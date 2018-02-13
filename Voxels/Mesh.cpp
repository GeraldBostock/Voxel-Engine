#include "Mesh.h"



Mesh::Mesh()
{
	glGenVertexArrays(1, &m_vaoID);
}


Mesh::~Mesh()
{
}

void Mesh::generateMesh(std::vector<blockTypes>* terrain)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				blockTypes type = terrain->at(i * 256 * 64 + j * 64 + k);

				if (type != AIR && type != WATER)
				{
					if (i == 0) addFace(glm::vec3((float)i, k, (float)j), LEFT, type);
					else if (i == 255) addFace(glm::vec3((float)i, k, (float)j), RIGHT, type);
					else
					{
						if (!isSolid(terrain->at((i - 1) * 256 * 64 + j * 64 + k))) addFace(glm::vec3((float)i, k, (float)j), LEFT, type);
						if (!isSolid(terrain->at((i + 1) * 256 * 64 + j * 64 + k))) addFace(glm::vec3((float)i, k, (float)j), RIGHT, type);
					}

					if (j == 0) addFace(glm::vec3((float)i, k, (float)j), BACK, type);
					else if (j == 255) addFace(glm::vec3((float)i, k, (float)j), FRONT, type);
					else
					{
						if (!isSolid(terrain->at(i * 256 * 64 + (j - 1) * 64 + k))) addFace(glm::vec3((float)i, k, (float)j), BACK, type);
						if (!isSolid(terrain->at(i * 256 * 64 + (j + 1) * 64 + k))) addFace(glm::vec3((float)i, k, (float)j), FRONT, type);
					}

					if (k == 0) addFace(glm::vec3((float)i, k, (float)j), BOTTOM, type);
					else if (k == 63) addFace(glm::vec3((float)i, k, (float)j), TOP, type);
					else
					{
						if (!isSolid(terrain->at(i * 256 * 64 + j * 64 + (k - 1)))) addFace(glm::vec3((float)i, k, (float)j), BOTTOM, type);
						if (!isSolid(terrain->at(i * 256 * 64 + j * 64 + (k + 1)))) addFace(glm::vec3((float)i, k, (float)j), TOP, type);
					}
				}
			}
		}
	}

	loadMeshToVao();
}

void Mesh::generateWaterMesh(std::vector<blockTypes>* terrain)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				blockTypes type = terrain->at(i * 256 * 64 + j * 64 + k);

				if (terrain->at(i * 256 * 64 + j * 64 + k) == WATER)
				{
					if (i == 0) addFace(glm::vec3((float)i, k, (float)j), LEFT, type);
					else if (i == 255) addFace(glm::vec3((float)i, k, (float)j), RIGHT, type);
					else
					{
						if (terrain->at((i - 1) * 256 * 64 + j * 64 + k) == AIR) addFace(glm::vec3((float)i, k, (float)j), LEFT, type);
						if (terrain->at((i + 1) * 256 * 64 + j * 64 + k) == AIR) addFace(glm::vec3((float)i, k, (float)j), RIGHT, type);
					}

					if (j == 0) addFace(glm::vec3((float)i, k, (float)j), BACK, type);
					else if (j == 255) addFace(glm::vec3((float)i, k, (float)j), FRONT, type);
					else
					{
						if (terrain->at(i * 256 * 64 + (j - 1) * 64 + k) == AIR) addFace(glm::vec3((float)i, k, (float)j), BACK, type);
						if (terrain->at(i * 256 * 64 + (j + 1) * 64 + k) == AIR) addFace(glm::vec3((float)i, k, (float)j), FRONT, type);
					}

					if (k == 0) addFace(glm::vec3((float)i, k, (float)j), BOTTOM, type);
					else if (k == 63) addFace(glm::vec3((float)i, k, (float)j), TOP, type);
					else
					{
						if (terrain->at(i * 256 * 64 + j * 64 + (k - 1)) == AIR) addFace(glm::vec3((float)i, k, (float)j), BOTTOM, type);
						if (terrain->at(i * 256 * 64 + j * 64 + (k + 1)) == AIR) addFace(glm::vec3((float)i, k, (float)j), TOP, type);
					}
				}
			}
		}
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

	glm::vec2* uvs;
	uvs = new glm::vec2[meshVertexCount];

	for (int i = 0; i < meshVertexCount; i++)
	{
		positions[i] = m_mesh.at(i).getPosition();
		normals[i] = m_mesh.at(i).getNormal();
		uvs[i] = m_mesh.at(i).getUv();
	}

	storeDataInAttributeList(0, positions, meshVertexCount);
	storeDataInAttributeList(1, normals, meshVertexCount);
	storeUvData(2, uvs, meshVertexCount);

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

void Mesh::storeUvData(int attributeNumber, glm::vec2* data, int count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(data[0]), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 2, GL_FLOAT, GL_FALSE, 0, 0);

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

void Mesh::addFace(glm::vec3 position, cubeFaces face, blockTypes blockType)
{
	glm::mat4 transMatrix = Maths::CreateTransformationMatrix(position, 0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec2* uvs;
	if(face == TOP && blockType == GRASS) uvs = m_atlas.getUv(T_GRASS_TOP);
	else if(blockType == GRASS) uvs = m_atlas.getUv(T_GRASS_SIDE);
	else if(blockType == DIRT) uvs = m_atlas.getUv(T_DIRT);
	else if(blockType == WATER) uvs = m_atlas.getUv(T_WATER);
	else uvs = m_atlas.getUv(T_SAND);

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

		if (face == BOTTOM || face == BACK)
		{
			m_mesh.push_back(Vertex(transformedPos, transformedNorm, uvs[5 - i]));
		}
		else
		{
			m_mesh.push_back(Vertex(transformedPos, transformedNorm, uvs[i]));
		}		
	}
}

bool Mesh::isSolid(blockTypes type)
{
	if (type == AIR || type == WATER) return false;

	return true;
}

GLuint Mesh::loadTexture()
{
	SDL_Surface* surface;
	surface = IMG_Load("res/texture.png");
	if (surface == NULL)
		printf("Could not load texture: %s\n", IMG_GetError());

	int Mode = GL_RGB;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);*/

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}
