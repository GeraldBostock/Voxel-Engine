#pragma once
#include <glm.hpp>

class Vertex
{
public:
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv);
	~Vertex();

	glm::vec3 getPosition();
	glm::vec3 getNormal();
	glm::vec2 getUv();

private:
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_uv;
};

