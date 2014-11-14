#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <string>
#include "Component.h"
#include "ResourceManager.h"

using namespace std;

// Basically keeps track of how the Entity is rendered.
// Keeps track of frame, rotation, and passes the details
// when rendering to the more low-level parts of the program

class AnimationComponent : public Component
{

private:
	string				animationResourceID;
	ResourceManager*	resourceHandle;
	Animation*			animationResource;

	int					frameIndex;
	float				currentFrameTime;

	class AnimationBucket : protected Buffer
	{

	};

public:
	
	AnimationComponent	(ResourceManager* resourceHandle, 
							string animationResourceID);
	~AnimationComponent	();

	void				update(float dt);
	void				draw();


	Buffer*				newBuffer();
	void				applyBuffer();
};

#endif