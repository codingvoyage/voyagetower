#ifndef MAP_H
#define MAP_H

#include <string>
#include "Services.h"
#include "tmx/Tmx.h"

// Here's how this works. The Map will be responsible
// for loading and unloading resources, and providing
// the access to the right resources for a Camera
// class. The Camera class will be responsible for
// actually rendering the map.

using namespace std;

class Map
{
public:
	// Constructor loads the tmx map
	Map();
	~Map();

	// for debug purposes, postpone the camera class
	void	draw();

private:
	// Loads the thing into memory
	void loadMap();
	Tmx::Map* tmxMap;

	


};


#endif