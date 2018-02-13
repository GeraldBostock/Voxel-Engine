#include "Chunk.h"



Chunk::Chunk(unsigned char* terrain)
{
	m_terrain.reserve(CHUNK_X * CHUNK_Y * CHUNK_Z);

	for (int i = 0; i < CHUNK_X; i++)
	{
		for (int j = 0; j < CHUNK_Z; j++)
		{
			int k = 0;
			for (; k < terrain[i * CHUNK_X + j] / 4; k++)
			{
				if (k == terrain[i * CHUNK_X + j] / 4 - 1 && k > WATER_LEVEL + 1) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = GRASS;
				else if(k == terrain[i * CHUNK_X + j] / 4 - 1 && k <= WATER_LEVEL + 1) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = SAND;
				else if(k >= 0 && k <= WATER_LEVEL + 1) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = SAND;
				else m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = DIRT;
			}

			for (; k < CHUNK_Y; k++) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = AIR;
		}
	}

	for (int i = 0; i < CHUNK_X; i++)
	{
		for (int j = 0; j < CHUNK_Z; j++)
		{
			for (int k = 0; k < WATER_LEVEL; k++)
			{
				if(k >= 0 && k <= 3) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = DIRT;
				else if (m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] == AIR) m_terrain[i * CHUNK_Y * CHUNK_Z + j * CHUNK_Y + k] = WATER;
			}
		}
	}

	m_terrainMesh.generateMesh(&m_terrain);
	m_waterMesh.generateWaterMesh(&m_terrain);
}


Chunk::~Chunk()
{
}

Mesh* Chunk::getTerrainMesh()
{
	return &m_terrainMesh;
}

Mesh* Chunk::getWaterMesh()
{
	return &m_waterMesh;
}
