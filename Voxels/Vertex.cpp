#include "Vertex.h"



Vertex::Vertex(glm::vec3 position, glm::vec3 normal)
{
	m_position = position;
	m_normal = normal;
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