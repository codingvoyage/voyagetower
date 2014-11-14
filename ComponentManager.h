#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "Component.h"
#include "ComponentList.h"
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

// For convenience
//typedef unordered_map<ComponentType, ComponentList*> typeToListMap;

typedef unordered_map<ComponentType, ComponentList*> typeToListMap;

class ComponentManager
{

private:
	// GameObject, which maps objectIDs to collections of 
	// components working together which comprise one coherent object
	ComponentList			gameObjects;

	// Mapping from component type to the list of the components
	typeToListMap			componentLists;

public:

	ComponentManager();
	~ComponentManager();

	// There should be a destructor for calling the destructors of every single component.
	// GameObject, which contains a list of components, can be
	// easily modelled with the Component class
	class GameObject : public Component
	{
		// I can make this dynamic, but right now just give it a max
		// capacity of components
	public:
		static const int SIZE_LIMIT = 8;
		Component* components[SIZE_LIMIT];
		int dependencyCount = 0;

		GameObject() : Component(ComponentType::GAMEOBJECT)
		{
			// Set empty values to NULL
			for (int i = 0; i < SIZE_LIMIT; i++) components[i] = NULL;
		}
		~GameObject() {}

		// These are dummies to satisfy the interface
		void update(float dt) { }
		void applyBuffer() { }

	};

	// GameObject related things
	int						newGameObject();
	int						newGameObject(vector<Component*> components);
	GameObject*				getGameObject(int objID);

	// This is ugly and I'm considering making the game object manager
	// part of a separate class
	void					gameObjAddComponent(int objID, Component* c);
	bool					gameObjHasComponentOfType(int objID, ComponentType type);
	Component*				gameObjGetComponentOfType(int objID, ComponentType type);
	int						gameObjDependencyCount(int objID);
	void					gameObjRegisterDependency(int objID);
	void					gameObjRemoveDependency(int objID);

	// ComponentLists
	int addComponent		(Component* myComponent, ComponentType type);
	ComponentList*			getComponents(ComponentType type);

};

#endif