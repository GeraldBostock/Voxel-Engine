#pragma once
#include <array>
#include <vector>

#include "Mesh.h"
#include "Cube.h"

#define CHUNK_X		256
#define CHUNK_Z		256
#define CHUNK_Y		 64

#define WATER_LEVEL  25

class Chunk
{
public:
	Chunk(unsigned char* terrain);
	~Chunk();

	Mesh* getTerrainMesh();
	Mesh* getWaterMesh();

private:
	Mesh m_terrainMesh;
	Mesh m_waterMesh;

	std::vector<blockTypes> m_terrain = std::vector<blockTypes>(CHUNK_X * CHUNK_Y * CHUNK_Z);

	blockTypes getAtIndex(int i, int j, int k);
	void setAtIndex(int i, int j, int k);
};

