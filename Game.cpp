#include "Game.h"

Game::Game()
{
	// Start SDL
	int result = startSDL();
	if (result < 0) 
	{
		std::cout << "Failed to start SDL!\n";
		std::cout << "Error message: " << SDL_GetError() << "\n";
	}
	else
	{
		// If SDL started fine, then load resources.
		resource = new ResourceManager(renderer);
		loadResources();

		// Load many systems
		ProcessManager* process = new ProcessManager();
		LuaInterface* luaInterface = new LuaInterface();
		LogManager* logManager = new LogManager();
		ComponentManager* componentManager = new ComponentManager();

		Services::provide(resource);
		Services::provide(process);
		Services::provide(luaInterface);
		Services::provide(logManager);
		Services::provide(componentManager);

	} 

}

Game::~Game()
{
	std::cout << "Calling destructor.\n";

	// Delete all services, which calls their respective destructors
	delete Services::resourceManager();
	delete Services::processManager();
	delete Services::logManager();
	delete Services::luaInterface();
	delete Services::componentManager();

	// Destroy window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// Quit SDL subsystems
	SDL_Quit();

}

int Game::startSDL()
{
	// Null out variables to begin with.
	window = NULL;
	screenSurface = NULL;
	renderer = NULL;

	// Start SDL video systems
	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result < 0) return -1;

	// Create window
	window = SDL_CreateWindow(
		"Tower Defense", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN 
	);
	if (window == NULL) return -1;

	// Extract window's surface
	screenSurface = SDL_GetWindowSurface(window);
	
	// Setup hardware accelerated renderer.
	renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) return -1;
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	return 0;

}
void Game::loadResources()
{
	// Use Resource.cpp to load the specific graphics for the rudimentary game.

	// Loads all textures into memory
	ifstream myfile;
	myfile.open("res\\loadtextures.txt");
	if (myfile.is_open())
	{
		string line;
		string nextID;
		string nextFilepath;
		bool needsNextID = true;

		while ( getline (myfile,line) )
		{
			if (line == "") continue;
			if (needsNextID)
			{
				nextID = line;	
				needsNextID = false;
			} else {
				nextFilepath = line;
				resource->loadTexture(nextID, nextFilepath);
				needsNextID = true;
			}

#ifdef DEBUG
			cout << line << '\n';
#endif

		}
		myfile.close();
		myfile.clear();
	}
	
#ifdef DEBUG
	cout << "\nFinished loading textures\n\n";
#endif

	// Assemble textures into animations.
	ifstream animation;
	animation.open("res\\loadanimations.txt");
	if (animation.is_open())
	{
		string line;
		int frameCount;
		string animationID;
		string* textureIDs;
		float* delayTimes;

		// 0 - needs animationID, 1 - needs length,
		// 2 - needs textureID, 3 - needs corresponding delay
		int state = 0;
		int currentFrame = 0;

		while (getline(animation,line))
		{
			if (line == "") continue;

#ifdef DEBUG
			cout << line << ", and state: " << state << '\n';
#endif

			switch (state)
			{
				// Read animationID, move on to read length
				case 0:
					animationID = line;
					state = 1;
					break;

				// Read length, move on to read textureID
				case 1:
					frameCount = atoi(line.c_str());
					textureIDs = new string[frameCount];
					delayTimes = new float[frameCount];
					state = 2;
					break;

				// Read textureID, move on to frame delay
				case 2:
					textureIDs[currentFrame] = line;
					state = 3;
					break;

				// Read delay, either finish or next textureID
				case 3:
					float delay = (float)atof(line.c_str());
					delayTimes[currentFrame] = delay;
					currentFrame++;

					if (currentFrame == frameCount)
					{
						// Done with this one.
						resource->addMultiTexAnimation(
							textureIDs, 
							delayTimes, 
							frameCount, 
							animationID);

						// Reset state
						currentFrame = 0;
						state = 0;
					}
					else
					{
						// Need more frames.
						state = 2;
					}

					break;

			}	// end switch

		} // end input loop

		animation.close();
	}

#ifdef DEBUG
	cout << "\nFinished loading animations\n\n";
#endif

}

void Game::MainLoop()
{
	int standardDelayMs = 50;
	bool isRunning = true;
	SDL_Event e;

	/*ComponentManager* componentManager = Services::componentManager();

	AnimationComponent* component = new AnimationComponent(resource, "creep2green");
	PhysicsComponent* physics = new PhysicsComponent(0.0f, 0.0f, 0.0f, 0.0f);

	componentManager->addComponent(physics, ComponentType::PHYSICS);
	componentManager->addComponent(component, ComponentType::ANIMATION);

	vector<Component*> v;
	v.push_back(component);
	v.push_back(physics);
	int newobj = componentManager->newGameObject(v);
*/
	// Note- there is still unimplemented funcitonality!
	// Something about GameObject and its knowing whether to die or
	// not depending on whether it has any references yet. Please
	// somehow handle that?

	lua_State* L = Services::luaInterface()->L;


	luaL_dofile(L, "test1.lua");

	// Make a coroutine of moveEntity
	int coroutine = Services::luaInterface()->newCoroutine("testCoroutine");

	lua_getglobal(L, "resumeCoroutine");
	// Once to know what index is the coroutine,
	// a second time to give the coroutine its own number
	lua_pushinteger(L, coroutine);
	lua_pushinteger(L, coroutine);
	lua_call(L, 2, 0);


	// Event handler needs to be moved elsewhere.
	// Like, soon.
	while (isRunning)
	{
		// Poll events...
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_DOWN:
				case SDLK_LEFT:
				case SDLK_RIGHT:
					break;
				default:
					break;
				}
			}

		}

		// Handle the frame in a basic way
		SDL_RenderClear(renderer);

		//resource->getTexture("ship")->draw();
		//physics->newx((*myEntity)->getX());
		//physics->newy((*myEntity)->getY());
		ComponentList* list = Services::componentManager()->getComponents(ComponentType::ANIMATION);
		if (list != NULL)
		{
			for (int i = 0; i < list->getListSize(); i++)
			{
				Component* comp = list->getComponent(i);
				if (comp != NULL && comp->getState()
					== ComponentState::ALIVE)
				{
					((AnimationComponent*)comp)->draw();
				}
			}
		}


		// ALL UPDATING HAPPENS IN SECONDS
		float dt = (float)(standardDelayMs / 1000.0f);

		// Update all running processes. This is the section where
		// scripts are largely resumed too
		Services::processManager()->update(dt);

		// Update all the components of animation
		if (list != NULL) list->updateComponents(dt);


		SDL_RenderPresent(renderer);
		SDL_Delay(standardDelayMs);

	}


}