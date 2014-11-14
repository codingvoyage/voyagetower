#include "ProcessManager.h"

void ProcessManager::update(float dt)
{

	list<Process*>::iterator iter = processList.begin();

	int activeProcesses = 0;

	while (iter != processList.end())
	{
		bool isActive = (*iter)->isActive();

		if (isActive)
		{
			activeProcesses++;
			(*iter)->update(dt);
			iter++;
		}
		else
		{
			// First, clean it up.
			(*iter)->onFinish();
			delete *iter;

			cout << "Is finished!" << endl;

			// Remove the inactive process.
			iter = processList.erase(iter);
		}
	}

	//cout << "active processes: " << activeProcesses << ". " << endl;
}


void ProcessManager::addProcess(Process* p)
{
	processList.push_back(p);
}
