#ifndef MULTITEXTUREANIMATION_H
#define MULTITEXTUREANIMATION_H

#include <iostream>
#include "Animation.h"

class MultiTextureAnimation : public Animation
{
private:
	Texture** texture;

public:

	MultiTextureAnimation(Texture** textures, float* delays, int frameCount);
	virtual ~MultiTextureAnimation();

	void draw(int frameIndex, int screenX, int screenY);


};



#endif