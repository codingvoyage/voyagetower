#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include "Texture.h"

class Animation 
{

protected:
	float*			frameDurations;
	int				numFrames;

public:
	Animation();
	virtual ~Animation();

	virtual void	draw(int frameIndex, int screenX, int screenY);
	virtual void	draw(int frameIndex, int screenX, int screenY,
							Vector2 targetOrientation);

	int				getFrameCount();
	float			getFrameDuration(int frameIndex);


};

#endif