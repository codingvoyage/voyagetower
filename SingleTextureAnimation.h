#ifndef SINGLETEXTUREANIMATION_H
#define SINGLETEXTUREANIMATION_H

#include "Animation.h"
#include "Texture.h"

class SingleTextureAnimation : public Animation
{
	
private:
	Texture* texture;


public:

	SingleTextureAnimation(Texture* texture, float* delays, int frameCount);
	~SingleTextureAnimation();

	void draw(int frameIndex, int screenX, int screenY);



};

#endif