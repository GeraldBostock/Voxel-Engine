#pragma once
#include <glew.h>
#include <vector>
#include <SDL_image.h>
#include <time.h>
#include <random>

#include "Vertex.h"
#include "Helper\Maths.h"
#include "Cube.h"

class Mesh
{
public:
	Mesh(GLuint vaoID);
	~Mesh();

	void generateMesh(unsigned char* terrain);
	void loadMeshToVao();
	void storeDataInAttributeList(int attributeNumber, glm::vec3* data, int count);

	int getVertexCount();
	GLuint getVaoID();

private:
	void addFace(glm::vec3 position, cubeFaces face);

	GLuint m_vaoID;
	std::vector<Vertex> m_mesh;
};

