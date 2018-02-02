#pragma once
#include <glew.h>
#include <string>
#include <glm.hpp>
#include <fstream>
#include <stdio.h>
#include <gtc\type_ptr.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void init(std::string vertexFile, std::string fragmentFile);
	void start();
	void stop();
	void cleanUp();

protected:
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;

	GLint getUniformLocation(std::string uniformName);
	void bindAttribute(int attribute, std::string variableName);
	GLuint loadShader(std::string shaderPath, GLenum shaderType);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	void loadVector(GLint location, glm::vec3 vector);
	void loadMatrix(GLint location, glm::mat4 matrix);

private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};

