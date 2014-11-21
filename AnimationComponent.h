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

	// The vector which describes how the component is oriented.

	// The issue is that SDL rotates images clockwise,
	// but it's easier for API users to rotate them counterclockwise
	// because it's more like the mathematics we learned in school
	Vector2				orientation;


	class AnimationBucket : protected Buffer
	{

	};

public:
	
	AnimationComponent	(ResourceManager* resourceHandle, 
							string animationResourceID);
	~AnimationComponent	();

	// Change rotation
	// This vector doesn't have to be a unit vector.
	void				setDirection(float ux, float uy);

	// Where theta is relative to <1, 0>
	// Theta should be in 
	void				setDirectionDegrees(double theta);
	void				setDirectionRads(double theta);


	void				update(float dt);
	void				draw();


	Buffer*				newBuffer();
	void				applyBuffer();
};

#endif