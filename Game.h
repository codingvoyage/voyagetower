#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
#include <lua.hpp>

#include "ResourceManager.h"
#include "ProcessManager.h"
#include "AnimationComponent.h"
#include "Services.h"
#include "LogManager.h"
#include "LuaInterface.h"
#include "PhysicsComponent.h"


class Game 
{

private:
	SDL_Window*			window;
	SDL_Surface*		screenSurface;
	SDL_Renderer*		renderer;

	ResourceManager*	resource;

	int					startSDL();					//Initialize SDL systems

public:
	static const int	SCREEN_WIDTH = 640;
	static const int	SCREEN_HEIGHT = 480;

	Game				();
	~Game				();

	void				MainLoop();




};

#endif