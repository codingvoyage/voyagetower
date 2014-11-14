#include "Texture.h"

Texture::Texture() {}

Texture::Texture(SDL_Texture* resource, int width, int height, 
				 SDL_Renderer* renderer)
	: resource(resource), 
	  width(width),
	  height(height),
	  renderer(renderer)
{

}

Texture::~Texture()
{
	// Deallocate texture
	std::cout << "Deallocating texture.\n";
	SDL_DestroyTexture(resource);
}


// Fill the screen with this texture
void Texture::draw()
{
	SDL_RenderCopy(renderer, resource, NULL, NULL);
}

// Draw the entire texture at the provided screenCoordinates
void Texture::draw(int screenX, int screenY)
{
	SDL_Rect screenCoords;
	screenCoords.x = screenX;
	screenCoords.y = screenY;
	screenCoords.w = width;
	screenCoords.h = height;

	SDL_RenderCopy(renderer, resource, NULL, &screenCoords); 
}

void Texture::draw(int textureX, int textureY, 
				   int textureWidth, int textureHeight, 
				   int screenX, int screenY)
{
	SDL_Rect texturePortion;
	texturePortion.x = textureX;
	texturePortion.y = textureY;
	texturePortion.w = textureWidth;
	texturePortion.h = textureHeight;

	SDL_Rect screenCoords;
	screenCoords.x = screenX;
	screenCoords.y = screenY;
	screenCoords.w = width;
	screenCoords.h = height;


	SDL_RenderCopy(renderer, resource, &texturePortion, &screenCoords);
}


int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
