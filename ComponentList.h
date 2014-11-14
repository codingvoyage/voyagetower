#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include "Component.h"
#include <iostream>
#include <vector>

using namespace std;

// You can be assured that a valid index with nothing in it
// has been defaulted to NULL = 0
class ComponentList
{
private:
	vector<Component*> components;
	int sizeLimit;

	// index of current probe through components on list
	int probeIndex;

	// number of components, of any state
	int size;

	static const int DEFAULT = 200;
public:
	ComponentList();
	~ComponentList();


	int getListSize() { return sizeLimit; }
	int addComponent(Component* newComponent);
	Component* getComponent(int componentID);
	void updateComponents(float dt);

};

#endif