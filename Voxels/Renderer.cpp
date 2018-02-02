#include "Renderer.h"



Renderer::Renderer()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->getVaoID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);
}
