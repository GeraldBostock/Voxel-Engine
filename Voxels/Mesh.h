#pragma once
#include <glew.h>
#include <vector>
#include <SDL_image.h>
#include <time.h>
#include <random>
#include <array>

#include "Vertex.h"
#include "Helper\Maths.h"
#include "Cube.h"
#include "TextureAtlas.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void generateMesh(std::vector<blockTypes>* terrain);
	void generateWaterMesh(std::vector<blockTypes>* terrain);
	void loadMeshToVao();
	void storeDataInAttributeList(int attributeNumber, glm::vec3* data, int count);
	void storeUvData(int attributeNumber, glm::vec2* data, int count);
	GLuint loadTexture();

	int getVertexCount();
	GLuint getVaoID();

private:
	void addFace(glm::vec3 position, cubeFaces face, blockTypes blockType);
	bool isSolid(blockTypes blockType);

	TextureAtlas m_atlas;

	GLuint m_vaoID;
	GLuint m_waterVaoID;
	std::vector<Vertex> m_mesh;
};

