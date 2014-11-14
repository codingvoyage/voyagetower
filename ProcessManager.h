#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <iostream>
#include <list>
#include "Process.h"

using namespace std;

class ProcessManager {

private:
	list<Process*>		processList;


public:
	void				addProcess(Process* p);
	void				update(float dt);




};

#endif