#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "Animation.h"
#include "MultiTextureAnimation.h"

using namespace std;

// Loads resources, maps them to string IDs.

class ResourceManager
{
	
private:
	SDL_Renderer*			renderer;
	map<string, Texture*>	idToTexture;
	map<string, Animation*> idToAnimation;
	
	Texture*				loadPNGTexture(string filepath);

public:
	ResourceManager			(SDL_Renderer* renderer);
	~ResourceManager		();

	void					loadDefaultResources();

	Texture*				getTexture(string id);
	Animation*				getAnimation(string id);
	
	void					loadTexture(string textureID, string filepath);
	void					addMultiTexAnimation(string* textureIDs, 
								float* delays,
								int frameCount,
								string animationID);

};

#endif