#include "ResourceManager.h"
#include <fstream>

ResourceManager::ResourceManager(SDL_Renderer* renderer)
	: renderer(renderer)
{
	int imgFlags = IMG_INIT_PNG;
	int success = IMG_Init(imgFlags);

	// Load the test texture.
	loadTexture("ship", "res/ship.png");

	// Assemble animation...

}

ResourceManager::~ResourceManager()
{
	// Iterate through all textures and deallocate them all
	for (map<string, Texture*>::iterator i = idToTexture.begin(); 
		i != idToTexture.end(); i++)
	{
		// For iterator, i->second = value
		Texture* wrappedTexture = i->second;
		delete wrappedTexture;
	}

	// Same goes for animations
	for (map<string, Animation*>::iterator i = idToAnimation.begin(); 
		i != idToAnimation.end(); i++)
	{
		std::cout << "here we are in the animation deallocation loop.\n";
		Animation* animationResource = i->second;
		delete animationResource;
	}

	// Stop SDL_Image
	IMG_Quit();

}

void ResourceManager::loadDefaultResources()
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

		while (getline(myfile, line))
		{
			if (line == "") continue;
			if (needsNextID)
			{
				nextID = line;
				needsNextID = false;
			}
			else {
				nextFilepath = line;
				loadTexture(nextID, nextFilepath);
				needsNextID = true;
			}

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

		while (getline(animation, line))
		{
			if (line == "") continue;

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
					addMultiTexAnimation(
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


}


void ResourceManager::loadTexture(string textureID, string filepath)
{
	Texture* wrappedTexture = loadPNGTexture(filepath);
	if (wrappedTexture == NULL)
	{
		cout << "Error loading PNG texture resource.\n";
	}
	else
	{
		idToTexture[textureID] = wrappedTexture;
	}
}


void ResourceManager::addMultiTexAnimation(string* textureIDs,
									float* delays,
									int frameCount,
									string animationID)
{
	// Assemble list of textures
	Texture** textures = new Texture*[frameCount]; 
	for (int i = 0; i < frameCount; i++)
	{
		textures[i] = getTexture(textureIDs[i]);
	}

	Animation* newAnimation = new MultiTextureAnimation(textures, delays, frameCount);
	idToAnimation[animationID] = newAnimation;

}


// Get texture from the id
Texture* ResourceManager::getTexture(string id)
{
	return idToTexture[id];
}

// Get animation from the id
Animation* ResourceManager::getAnimation(string id)
{
	return idToAnimation[id];
}

// Loading function which takes care of loading Texture
// using SDL_Image
Texture* ResourceManager::loadPNGTexture(string filepath)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = NULL;

	loadedSurface = IMG_Load(filepath.c_str());
	if (loadedSurface != NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		Texture* wrappedTexture = new Texture(
			newTexture,
			loadedSurface->w,
			loadedSurface->h,
			renderer);

		SDL_FreeSurface(loadedSurface);

		return wrappedTexture;
	}
	else
	{
		std::cout << "Error loading image resource!\n";
		return NULL;
	}

}

