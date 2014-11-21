#include "SingleTextureAnimation.h"


// Note to self - refactor Animation so that this stuff doesn't require alternate names
// for delays, and framecount
// Also this needs to assign the boundaries of each frame from the texture too...

SingleTextureAnimation::SingleTextureAnimation(Texture* texture, float* delays, int frameCount)
	: texture(texture)
{
	frameDurations = delays;
	numFrames = frameCount;
}

SingleTextureAnimation::~SingleTextureAnimation()
{

}

void SingleTextureAnimation::draw(int frameIndex, int screenX, int screenY)
{
	// To be implemented
}


void SingleTextureAnimation::draw(int frameIndex, int screenX, int screenY,
	Vector2 targetOrientation)
{

}