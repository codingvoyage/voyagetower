#include <SDL.h>
#include <iostream>
#include "Game.h"


// Game entry point

int main(int argc, char* argv[]) {

	Game* g = new Game();
	g->MainLoop();
	delete g;

	// Pause and let me read debug messages
	int wait = 0;
	std::cin >> wait;

	return 0;
}
