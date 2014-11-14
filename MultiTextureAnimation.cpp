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