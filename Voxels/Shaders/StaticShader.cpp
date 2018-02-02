#include "StaticShader.h"



StaticShader::StaticShader(std::string vertexFile, std::string fragmentFile)
{
	super::init(vertexFile, fragmentFile);
}


StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	super::bindAttribute(0, "position");
	super::bindAttribute(1, "normal");
}

void StaticShader::getAllUniformLocations()
{
	m_projectionMatrixLocation = super::getUniformLocation("projectionMatrix");
	m_viewMatrixLocation = super::getUniformLocation("viewMatrix");
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	super::loadMatrix(m_projectionMatrixLocation, matrix);
}

void StaticShader::loadViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw());
	super::loadMatrix(m_viewMatrixLocation, viewMatrix);
}
