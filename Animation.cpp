#include "Animation.h"


Animation::Animation()
{

}

Animation::~Animation()
{
	//std::cout << "oh no. we're not supposed to call this.\n";
}

void Animation::draw(int frameIndex, int screenX, int screenY)
{

}


void Animation::draw(int frameIndex, int screenX, int screenY,
	Vector2 targetOrientation)
{

}

int Animation::getFrameCount()
{
	return numFrames;
}

float Animation::getFrameDuration(int frameIndex)
{
	return frameDurations[frameIndex];
}