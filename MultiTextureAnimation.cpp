#include "MultiTextureAnimation.h"



MultiTextureAnimation::MultiTextureAnimation(Texture** textures, float* delays, int frameCount)
{
	texture = textures; 
	frameDurations = delays;
	numFrames = frameCount;

}

MultiTextureAnimation::~MultiTextureAnimation()
{
	std::cout << "Calling multi-texture animation destructor.\n";
	delete[] texture;
	delete[] frameDurations;

}

void MultiTextureAnimation::draw(int frameIndex, int screenX, int screenY)
{
	texture[frameIndex]->draw(screenX, screenY);
}

void MultiTextureAnimation::draw(int frameIndex, int screenX, int screenY, Vector2 targetOrientation)
{
	Texture* t = texture[frameIndex];
	texture[frameIndex]->draw(0, 0,
		t->getWidth(), t->getHeight(), 
		screenX, screenY, 
		targetOrientation, false, false);
}