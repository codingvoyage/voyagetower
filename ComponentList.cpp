#include "ComponentList.h"

ComponentList::ComponentList()
{
	sizeLimit = DEFAULT;
	probeIndex = 0;
	size = 0;
	components.resize(DEFAULT);
	// Not sure if this is necessary
	for (int i = 0; i < DEFAULT; i++)
	{
		components[i] = NULL;
	}
}

// It doesn't matter where the components were
// constructed (mostly within factory methods). They
// reside here now and are updated from within ComponentList
// so free them from here
ComponentList::~ComponentList()
{
	// Untested code, please test it.
	for (int i = 0; i < sizeLimit; i++)
	{
		Component* targetForDeletion = components[i];
		if (targetForDeletion != NULL)
			delete targetForDeletion;
	}

}

// Needs CLOSER INSPECTIONS to check for off-by-one errors.
int ComponentList::addComponent(Component* newComponent)
{
	int numberAttempted = 0;
	//cout << "let's go." << endl;
	while (true)
	{
		cout << probeIndex << endl;
		if (numberAttempted == sizeLimit)
		{
			//cout << "REALLOC" << endl;
			// Indices all filled, allocate more memory
			probeIndex = sizeLimit;
			sizeLimit *= 2;
			components.resize(sizeLimit);

			// Not sure if this is necessary, but do it anyway
			for (int i = probeIndex; i < sizeLimit; i++)
				components[i] = NULL;
		}
		else
		{
			// We found empty space, or a dead component
			Component* c = components[probeIndex];
			if (c == NULL)
			{
				// Note - size is only for non-NULL references, so
				// only increment when a NULL space is filled
				size++;
				break;
			}
			else if (c->getState() == ComponentState::DEAD)
			{
				// A component marked for deletion? Delete it, then
				// offer up the location in the vector
				delete c;
				break;
			}
			else
			{
				// Not found? Keep searching
				probeIndex++;
				if (probeIndex >= sizeLimit) probeIndex = 0;
				numberAttempted++;
			}

		}

	}

	//std::cout << "ADDED A NEW AT INDEX " << probeIndex << "." << std::endl;
	// The index we found it on.
	components[probeIndex] = newComponent;
	return probeIndex;
}


Component* ComponentList::getComponent(int componentID)
{
	return components[componentID];
}


void ComponentList::updateComponents(float dt)
{
	// Not sure if this will make it faster, but let's try anyway
	int objectsTouched = 0;


	// Loop through and update all components
	for (int i = 0; i < components.size(); i++)
	{
		Component* c = components[i];
		if (c != NULL && c->getState() == ComponentState::ALIVE)
		{
			objectsTouched++;
			c->update(dt);
		}

		// Avoid doing extra checks.
		if (objectsTouched == size) return;
	}
	// no way
	/*
	if (components )
	vector<Component*>::iterator iter = components.begin();
	while (iter != components.end())
	{
		Component* c = *iter;
		if (c != NULL && c->getState() == ComponentState::ALIVE)
		{
			objectsTouched++;
			c->update(dt);
		}

		// Avoid doing extra checks.
		if (objectsTouched == size) return;

		iter++;
	}
	*/

}