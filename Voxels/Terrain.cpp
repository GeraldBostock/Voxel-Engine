#include "Terrain.h"



Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

unsigned char* Terrain::GenerateTerrain()
{
	SDL_Surface* surface = IMG_Load("res/map.jpg");
	if (surface == NULL)
		printf("Could not load from file: %s", IMG_GetError());
	unsigned char* pixels = (unsigned char*)surface->pixels;
	unsigned char* heightMap = new unsigned char[surface->w * surface->h];

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			heightMap[i * surface->w + j] = pixels[3 * (i * surface->w + j)];
			/*for (int k = 0; k < pixels[3 * (i * surface->w + j) / 25]; k++)
				heightMap[i * surface->w + j] = pixels[3 * (i * surface->w + j)];*/
		}
	}

	return heightMap;
}
