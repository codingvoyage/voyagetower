#include "ComponentManager.h"

typedef ComponentManager::GameObject GameObject;

ComponentManager::ComponentManager()
{
	// Nothing to do
}

// Component Manager 
// 1. creates and houses all gameobjects
// 2. houses all components
// This should be the centre of freeing their memory too
ComponentManager::~ComponentManager()
{
	cout << "ComponentManager now will deallocate lists." << endl;

	typeToListMap::iterator lists = componentLists.begin();
	while (lists != componentLists.end())
	{
		// Please check if this works
		ComponentList* currentList = (*lists).second;
		delete currentList;
		lists++;

	}

}

// Game-Object related things

int ComponentManager::newGameObject()
{
	GameObject* g = new GameObject();
	return gameObjects.addComponent(g);
}

// For convenience
int ComponentManager::newGameObject(vector<Component*> components)
{
	int objID = newGameObject();
	cout << "Constructing new GameObject at ID " << objID << "." << endl;
	for (int i = 0; i < components.size(); i++)
	{
		Component* c = components[i];
		c->setParentObjectID(objID);
		gameObjAddComponent(objID, c);
	}

	return objID;
}

// Utility method
GameObject*	ComponentManager::getGameObject(int objID)
{
	return (GameObject*)gameObjects.getComponent(objID);
}

void ComponentManager::gameObjAddComponent
	(int objID, Component* c)
{
	// You should validate objID first.

	// Get the gameobject being referenced
	//cout << ".." << endl;
	GameObject* object = getGameObject(objID);
	//cout << "Obj id " << objID << endl;
	//cout << ",," << endl;
	for (int i = 0; i < GameObject::SIZE_LIMIT; i++)
	{
		Component* current = object->components[i];
		if (current == NULL)
		{
			object->components[i] = c;
			return;
		}
	}

	// Announce error if we ran out of space for new components
}

bool ComponentManager::gameObjHasComponentOfType(int objID, ComponentType type)
{
	return gameObjGetComponentOfType(objID, type) != NULL;
}

Component* ComponentManager::gameObjGetComponentOfType(int objID, ComponentType type)
{
	GameObject* object = getGameObject(objID);
	if (object == NULL) cout << "We have a problem." << endl;
	for (int i = 0; i < GameObject::SIZE_LIMIT; i++)
	{
		Component* current = object->components[i];
		if (current != NULL)
		{
			if (current->getType() == type)
				return current;
		}
	}
	return NULL;
}

// Counting the number of dependencies
int ComponentManager::gameObjDependencyCount(int objID)
{
	GameObject* object = getGameObject(objID);
	return object->dependencyCount; 
}

void ComponentManager::gameObjRegisterDependency(int objID)
{
	GameObject* object = getGameObject(objID);
	object->dependencyCount++; 
}

void ComponentManager::gameObjRemoveDependency(int objID) {

	GameObject* object = getGameObject(objID);
	if (object->dependencyCount > 0) object->dependencyCount--;
}


// ComponentList-related things:
int ComponentManager::addComponent(Component* myComponent, ComponentType type)
{
	typeToListMap::const_iterator iter;
	iter = componentLists.find(type);

	if (iter == componentLists.end())
	{
		cout << "Adding new type of component" << endl;
		ComponentList* newList = new ComponentList();
		componentLists[type] = newList;
		return newList->addComponent(myComponent);
		// Not found, make new ones
	}
	else
	{
		cout << "Adding existing type of component" << endl;
		// Find existing list, and return the index
		ComponentList* existingList = iter->second;
		return existingList->addComponent(myComponent);
	}
}

ComponentList* ComponentManager::getComponents(ComponentType type)
{
	// the componentlists[type] before apparently initialized it prematurely
	// that took 15 minutes for me to figure out.
	typeToListMap::iterator iter = componentLists.find(type);
	if (iter == componentLists.end()) return NULL;
	else return iter->second;
}

