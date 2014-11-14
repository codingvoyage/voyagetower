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
	animationResource->draw(frameIndex, p->getx(), p->gety());
}

void AnimationComponent::applyBuffer()
{
	//Do nothing
	//Eventually this will buffer changes to the Animation state.
}
