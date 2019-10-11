#include "Shader.h"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	vertexShaderSource = ReadHelper::readTo(vertexPath);

	int success;
	char infoLog[logBufferSize];

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, logBufferSize, NULL, infoLog);
		throw GetShaderException(infoLog);
	}
	

	fragmentShaderSource = ReadHelper::readTo(fragmentPath);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, logBufferSize, NULL, infoLog);
		throw GetShaderException(infoLog);
	}
	

    id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, logBufferSize, NULL, infoLog);
		throw GetProgrammException(infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader()
{
	
}

GLuint Shader::getId()
{
	return id;
}
