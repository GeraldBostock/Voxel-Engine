#pragma once
#include <glm.hpp>

class Vertex
{
public:
	Vertex(glm::vec3 position, glm::vec3 normal);
	~Vertex();

	glm::vec3 getPosition();
	glm::vec3 getNormal();

private:
	glm::vec3 m_position;
	glm::vec3 m_normal;
};

