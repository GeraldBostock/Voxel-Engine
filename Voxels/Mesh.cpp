#include "Mesh.h"



Mesh::Mesh(GLuint vaoID)
{
	m_vaoID = vaoID;
}


Mesh::~Mesh()
{
}

void Mesh::generateMesh(unsigned char* terrain)
{
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			addFace(glm::vec3((float)i, (float)terrain[i * 256 + j], (float)j), TOP);
			addFace(glm::vec3((float)i, (float)terrain[i * 256 + j], (float)j), LEFT);
			addFace(glm::vec3((float)i, (float)terrain[i * 256 + j], (float)j), RIGHT);
			addFace(glm::vec3((float)i, (float)terrain[i * 256 + j], (float)j), BACK);
			addFace(glm::vec3((float)i, (float)terrain[i * 256 + j], (float)j), FRONT);
		}

	loadMeshToVao();
}

void Mesh::loadMeshToVao()
{
	glBindVertexArray(m_vaoID);

	int meshVertexCount = m_mesh.size();

	glm::vec3* positions;
	positions = new glm::vec3[meshVertexCount];

	glm::vec3* normals;
	normals = new glm::vec3[meshVertexCount];

	for (int i = 0; i < meshVertexCount; i++)
	{
		positions[i] = m_mesh.at(i).getPosition();
		normals[i] = m_mesh.at(i).getNormal();
	}

	storeDataInAttributeList(0, positions, meshVertexCount);
	storeDataInAttributeList(1, normals, meshVertexCount);

	glBindVertexArray(0);
}

void Mesh::storeDataInAttributeList(int attributeNumber, glm::vec3* data, int count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(data[0]), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Mesh::getVertexCount()
{
	return m_mesh.size();
}

GLuint Mesh::getVaoID()
{
	return m_vaoID;
}

void Mesh::addFace(glm::vec3 position, cubeFaces face)
{
	glm::mat4 transMatrix = Maths::CreateTransformationMatrix(position, 0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = faces[face][i].getPosition();
		glm::vec3 vertexNorm = faces[face][i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}

	/*Vertex topFace[] =
	{
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
	};

	Vertex frontFace[] = 
	{
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f))
	};

	Vertex backFace[] = 
	{
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f))
	};

	Vertex rightFace[] =
	{
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f))
	};

	Vertex leftFace[] =
	{
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f))
	};

	std::vector<Vertex> newFace;
	glm::mat4 transMatrix = Maths::CreateTransformationMatrix(position, 0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = topFace[i].getPosition();
		glm::vec3 vertexNorm = topFace[i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = frontFace[i].getPosition();
		glm::vec3 vertexNorm = frontFace[i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = backFace[i].getPosition();
		glm::vec3 vertexNorm = backFace[i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = rightFace[i].getPosition();
		glm::vec3 vertexNorm = rightFace[i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}

	for (int i = 0; i < 6; i++)
	{
		glm::vec3 vertexPos = leftFace[i].getPosition();
		glm::vec3 vertexNorm = leftFace[i].getNormal();

		glm::vec4 toTransformPos = glm::vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
		glm::vec4 transformedVec4Pos = transMatrix * toTransformPos;
		glm::vec3 transformedPos = glm::vec3(transformedVec4Pos.x, transformedVec4Pos.y, transformedVec4Pos.z);

		glm::vec4 toTransformNorm = glm::vec4(vertexNorm.x, vertexNorm.y, vertexNorm.z, 1.0f);
		glm::vec4 transformedVec4Norm = transMatrix * toTransformNorm;
		glm::vec3 transformedNorm = glm::vec3(transformedVec4Norm.x, transformedVec4Norm.y, transformedVec4Norm.z);

		m_mesh.push_back(Vertex(transformedPos, transformedNorm));
	}*/
}
