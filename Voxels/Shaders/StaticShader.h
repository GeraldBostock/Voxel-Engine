#pragma once
#include <string>
#include <glm.hpp>

#include "ShaderProgram.h"
#include "../Entities/Camera.h"
#include "../Helper/Maths.h"

class StaticShader : public ShaderProgram
{
public:
	typedef ShaderProgram super;

	StaticShader(std::string vertexFile, std::string fragmentFile);
	~StaticShader();

	void loadProjectionMatrix(glm::mat4 projectionMatrix);
	void loadViewMatrix(Camera camera);

protected:
	virtual void bindAttributes();
	virtual void getAllUniformLocations();

private:
	GLint m_projectionMatrixLocation;
	GLint m_viewMatrixLocation;
};

