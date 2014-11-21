#include "Texture.h"

Texture::Texture() {}

Texture::Texture(SDL_Texture* resource, int width, int height,
	SDL_Renderer* renderer)
	: resource(resource),
	width(width),
	height(height),
	renderer(renderer)
{
	// Doesn't point anywhere, means there isn't a orientation

	// Testing purposes - they face to the right.
	orientation.x = 1;
	orientation.y = 0;
}

Texture::Texture(SDL_Texture* resource, int width, int height,
	SDL_Renderer* renderer, float ux, float uy)
	: resource(resource),
	width(width),
	height(height),
	renderer(renderer)
{
	orientation.x = ux;
	orientation.y = uy;

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
	// The dimensions of that
	screenCoords.w = textureWidth;
	screenCoords.h = textureHeight;


	SDL_RenderCopy(renderer, resource, &texturePortion, &screenCoords);
}

// Accepts rotationAngle in RADIANS
void Texture::draw(int textureX, int textureY,
				int textureWidth, int textureHeight,
				int screenX, int screenY,
				Vector2 targetOrientation,
				bool flipHorizontal, bool flipVertical)
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

	// Handle flipping, useful for map rendering
	SDL_RendererFlip flip;
	if (flipHorizontal && flipVertical)
		flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (flipHorizontal) flip = SDL_FLIP_HORIZONTAL;
	else if (flipVertical) flip = SDL_FLIP_VERTICAL;
	else flip = SDL_FLIP_NONE;

	// Calculate degrees based on the default orientation and this new
	// vector. Remember it's degrees, and we count clockwise.

	// atan2 is good for getting the signed angle.
	// The negative makes up for the fact that we're doing CCW,
	// but SDL wants to do CW.

	float angle = -1*atan2(getDefaultOrientation().x*targetOrientation.y - 
		getDefaultOrientation().y*targetOrientation.x, 
		getDefaultOrientation().x*targetOrientation.x + 
		getDefaultOrientation().y*targetOrientation.y ); 

	// atan2 returns radians, SDL takes degrees.
	double degrees = (double)angle * (180 / M_PI);

	SDL_RenderCopyEx(renderer,
		resource,
		&texturePortion,
		&screenCoords,
		degrees,
		NULL, // rotate around the centre
		flip);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

Vector2 Texture::getDefaultOrientation()
{
	return orientation;
}

