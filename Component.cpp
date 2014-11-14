#include "Component.h"
#include "Services.h"

Component::Component(ComponentType type)
	: type(type)
{
	parentObjectID = -1;
	state = ComponentState::ALIVE;
}

Component::~Component()
{
	std::cout << "Component deleted!" << std::endl;
}

// A given Component can simply access other Components
// from the same Game Object
Component* Component::getComponent(ComponentType type)
{
	return Services::componentManager()->
		gameObjGetComponentOfType(parentObjectID, type);
}

ComponentType Component::getType()
{
	return type;
}

void Component::setParentObjectID(int newID)
{
	parentObjectID = newID;
}

// Methods which deal with the Component's state
ComponentState Component::getState()
{
	return state;
}

void Component::deactivate()
{
	state = ComponentState::INACTIVE;
}

void Component::kill()
{
	state = ComponentState::DEAD;
}