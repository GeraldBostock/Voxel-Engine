#pragma once
#include <glew.h>

#include "Mesh.h"
#include "Chunk.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare();
	void renderMesh(Mesh* mesh);
};

