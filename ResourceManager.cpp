#include "ResourceManager.h"


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

