#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(float x, float y, float vx, float vy)
	: Component(ComponentType::PHYSICS),
	x(x), y(y), vx(vx), vy(vy)
{

}

PhysicsComponent::~PhysicsComponent()
{

}

// ux and uy are the new direction vector.
// it is a normal vector.
float PhysicsComponent::newSpeed(float ux, float uy)
{
	// do nothing for now;
	return 0.0f;
}

float PhysicsComponent::getSpeed()
{
	return sqrt(vx*vx + vy*vy);
}

void PhysicsComponent::update(float dt)
{
	x += vx * dt;
	y += vy * dt;
}

// I think I AM going to buffer the physics-components
void PhysicsComponent::applyBuffer()
{
	// not yet
}