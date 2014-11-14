#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "SDL.h"

// Wraps a Texture

class Texture 
{

private:
	SDL_Texture*	resource;
	SDL_Renderer*	renderer;
	int				width;
	int				height;

public:
	Texture();
	Texture(		SDL_Texture* resource,
					int width, 
					int height,
					SDL_Renderer* renderer);
	~Texture();

	// Multiple draw functions for every variant SDL provides
	void			draw();
	void			draw(int screenX, int screenY);
	void			draw(int textureX, int textureY, 
						 int textureWidth, int textureHeight, 
						 int screenX, int screenY);

	int				getWidth();
	int				getHeight();


};



#endif