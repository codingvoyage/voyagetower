#ifndef COMPONENT_H
#define COMPONENT_H

#include "ComponentType.h"
#include <iostream>

enum ComponentState {
	ALIVE,
	INACTIVE,
	DEAD
};


class Component
{

protected:
	class Buffer
	{
	public:
		void				resetBuffer() { }
	};

	Component*				getComponent(ComponentType type);

private:
	// Type of the Component
	ComponentType			type;
	// Status - do we continue maintaining it?
	ComponentState			state;
	// Pool the next updates
	Buffer*					buffer;
	int						parentObjectID;

public:

	Component				(ComponentType type);
	~Component				();

	// For accessing other components of the same object
	ComponentType			getType();
	void					setParentObjectID(int newID);
	// State related
	ComponentState			getState();
	void					deactivate();
	void					kill();

	// Register component to be alerted to events

	// Once registered, events come in through this

	// Update function in behavior
	virtual void			update(float dt) = 0;

	// Specify how the buffer is made
	virtual void			applyBuffer() = 0;


};


#endif