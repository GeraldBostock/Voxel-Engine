#include "Vertex.h"



Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv)
{
	m_position = position;
	m_normal = normal;
	m_uv = uv;
}


Vertex::~Vertex()
{
}

glm::vec3 Vertex::getPosition()
{
	return m_position;
}

glm::vec3 Vertex::getNormal()
{
	return m_normal;
}

glm::vec2 Vertex::getUv()
{
	return m_uv;
}