#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

class Terrain
{
public:
	Terrain();
	~Terrain();

	unsigned char* GenerateTerrain();
};

