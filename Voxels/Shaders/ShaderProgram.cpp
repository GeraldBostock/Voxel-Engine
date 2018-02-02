#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{

}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::init(std::string vertexFile, std::string fragmentFile)
{
	m_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	m_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	bindAttributes();

	glLinkProgram(m_programID);
	checkShaderError(m_programID, GL_LINK_STATUS, true, "Program linking failed.\n");

	glValidateProgram(m_programID);
	checkShaderError(m_programID, GL_VALIDATE_STATUS, true, "Program invalid.\n");

	getAllUniformLocations();
}

void ShaderProgram::bindAttribute(int attribute, std::string variableName)
{
	glBindAttribLocation(m_programID, attribute, variableName.c_str());
}

GLint ShaderProgram::getUniformLocation(std::string uniformName)
{
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	return location;
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::loadVector(GLint location, glm::vec3 vector)
{
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::start()
{
	glUseProgram(m_programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_programID);
}

GLuint ShaderProgram::loadShader(std::string shaderPath, GLenum shaderType)
{
	std::ifstream file;
	file.open(shaderPath);

	std::string fileText;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			fileText.append(line + "\n");
		}
	}
	else
	{
		printf("Unable to open file at: %s", shaderPath.c_str());
	}

	GLuint shaderID = glCreateShader(shaderType);
	if (shaderID == 0)
		printf("Could not create shader\n");

	const GLchar* shaderSourceStrings[1];
	shaderSourceStrings[0] = fileText.c_str();

	GLint sourceStringLengths[1];
	sourceStringLengths[0] = fileText.length();

	glShaderSource(shaderID, 1, shaderSourceStrings, sourceStringLengths);
	glCompileShader(shaderID);
	checkShaderError(shaderID, GL_COMPILE_STATUS, false, "Could not compile shader.");

	return shaderID;
}

void ShaderProgram::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		printf("%s: %s\n", errorMessage.c_str(), error);
	}
}
