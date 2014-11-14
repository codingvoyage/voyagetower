#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"
#include <cmath>

class PhysicsComponent : public Component
{
private:
	// I am going to write a simple 2-D vector 
	// class at some point.
	float x, y;
	float vx, vy;



public:
	PhysicsComponent(float x, float y, float vx, float vy);
	~PhysicsComponent();

	// Getters and Setters
	float getx() { return x;  }
	float gety() { return y; }
	float getvx() { return vx; }
	float getvy() { return vy; }
	void newx(float nx) { x = nx; }
	void newy(float ny) { y = ny; }
	void newvx(float nx) { vx = nx; }
	void newvy(float ny) { vy = ny; }

	float newSpeed(float ux, float uy);
	float getSpeed();

	void update(float dt);
	void applyBuffer();

};

#endif