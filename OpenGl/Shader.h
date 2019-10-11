#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "ReadHelper.h"

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	GLuint getId();
private:
	GLuint id;

	char* vertexShaderSource;
	char* fragmentShaderSource;

	static const int logBufferSize = 512;
	class GetShaderException : public std::exception
	{
	private:
		std::string error;
	public:
		GetShaderException(const std::string& _error) : error(_error) { }
	};
	class GetProgrammException : public std::exception
	{
	private:
		std::string error;
	public:
		GetProgrammException(const std::string& _error) : error(_error) { }
	};
	
	friend class Run;
};

