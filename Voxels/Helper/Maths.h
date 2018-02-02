#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

const float m_pi = 3.14159265359f;

class Maths
{
public:
	inline Maths();
	inline ~Maths();

	inline static glm::mat4 CreateTransformationMatrix(glm::vec3 position, float rX, float rY, float rZ, float scale);
	inline static glm::mat4 CreateViewMatrix(glm::vec3 position, float pitch, float yaw);
	inline static glm::mat4 CreateProjectionMatrix(int wWidth, int wHeight, float fov, float nearPlane, float farPlane);
};

Maths::Maths()
{

}

Maths::~Maths()
{

}

glm::mat4 Maths::CreateTransformationMatrix(glm::vec3 position, float rX, float rY, float rZ, float scale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);

	matrix = glm::rotate(matrix, glm::radians(rX), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rY), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rZ), glm::vec3(0, 0, 1));

	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

	return matrix;
}

glm::mat4 Maths::CreateViewMatrix(glm::vec3 position, float pitch, float yaw)
{
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(pitch), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(yaw), glm::vec3(0, 1, 0));

	glm::vec3 cameraPos = position;
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);

	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

	return viewMatrix;
}

glm::mat4 Maths::CreateProjectionMatrix(int wWidth, int wHeight, float fov, float nearPlane, float farPlane)
{
	glm::mat4 projMatrix = glm::mat4(1.0f);

	float aspectRatio = (float)wWidth / (float)wHeight;
	float yScale = (float)(1.0f / tan((fov / 2.0f * glm::pi<float>()) / 180.0f)) * aspectRatio;
	float xScale = yScale / aspectRatio;
	float frustumLength = farPlane - nearPlane;

	projMatrix[0][0] = xScale;
	projMatrix[1][1] = yScale;
	projMatrix[2][2] = -((farPlane + nearPlane) / frustumLength);
	projMatrix[2][3] = -1;
	projMatrix[3][2] = -((2 * farPlane * nearPlane) / frustumLength);
	projMatrix[3][3] = 0;

	return projMatrix;
}
