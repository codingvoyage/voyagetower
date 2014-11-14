#include "Process.h"

bool Process::isActive()
{ 
	return active; 
}

void Process::deactivate()
{
	active = false;
}

Process::Process(){}
Process::~Process(){}