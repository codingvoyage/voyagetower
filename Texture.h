#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <cmath>
#include "Vector2.h"
#include "SDL.h"

// Wraps a Texture

class Texture 
{
	
private:
	SDL_Texture*	resource;
	SDL_Renderer*	renderer;
	int				width;
	int				height;

	//float			scale;
	Vector2			orientation;

public:
	Texture();
	Texture(		SDL_Texture* resource,
					int width, 
					int height,
					SDL_Renderer* renderer);

	Texture			(SDL_Texture* resource,
					int width,
					int height,
					SDL_Renderer* renderer,
					float ux, float uy);
	~Texture();

	// Multiple draw functions for every variant SDL provides
	void			draw();
	void			draw(int screenX, int screenY);
	void			draw(int textureX, int textureY, 
						 int textureWidth, int textureHeight, 
						 int screenX, int screenY);

	void			draw(int textureX, int textureY,
						 int textureWidth, int textureHeight,
						 int screenX, int screenY,
						 Vector2 targetOrientation,
						 bool flipHorizontal, bool flipVertical);

	// Getters for this Texture's features
	int				getWidth();
	int				getHeight();
	Vector2			getDefaultOrientation();

};



#endif