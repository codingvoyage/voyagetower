#include "AnimationComponent.h"
#include "PhysicsComponent.h"


AnimationComponent::AnimationComponent(ResourceManager* resourceHandle, 
	string animationResourceID)
	: Component(ComponentType::ANIMATION), 
	  resourceHandle(resourceHandle), 
	  animationResourceID(animationResourceID)
{
	animationResource = resourceHandle->getAnimation(animationResourceID);
	frameIndex = 0;
	currentFrameTime = 0.0f;

	// Make the default orientation that of the first texture in the
	// animation
	orientation.x = 0;
	orientation.y = 1;

}

AnimationComponent::~AnimationComponent()
{

}


void AnimationComponent::update(float dt)
{

	// Add time to the animation
	currentFrameTime += dt;

	if (currentFrameTime >= animationResource->getFrameDuration(frameIndex))
	{
		// If we exceed the frame duration, move on to the next frame
		currentFrameTime = 0.0f;
		frameIndex++;

		// If we overshoot, move the index to the beginning (0) instead.
		if (frameIndex == animationResource->getFrameCount())
		{
			frameIndex = 0;
		}

	}

}

void AnimationComponent::draw()
{
	PhysicsComponent* p;
	p = (PhysicsComponent*)getComponent(ComponentType::PHYSICS);
	//animationResource->draw(frameIndex, p->getx(), p->gety());

	animationResource->draw(frameIndex, p->getx(), p->gety(), 
		orientation);
}

// Mostly rotation/orientation related methods:

void AnimationComponent::setDirection(float ux, float uy)
{
	float magnitude = sqrt(ux*ux + uy*uy);
	orientation.x = ux / magnitude;
	orientation.y = uy / magnitude;
}

// Relative to the unit circle starting CCW from <1, 0>
void AnimationComponent::setDirectionDegrees(double theta)
{
	setDirectionRads(theta * (M_PI / 180));
}

void AnimationComponent::setDirectionRads(double theta)
{
	orientation.x = cos(theta);
	orientation.y = sin(theta);
}


void AnimationComponent::applyBuffer()
{
	//Do nothing
	//Eventually this will buffer changes to the Animation state.
}
