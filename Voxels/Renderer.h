#pragma once
#include <glew.h>

#include "Mesh.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void prepare();
	void renderMesh(Mesh* mesh);
};

