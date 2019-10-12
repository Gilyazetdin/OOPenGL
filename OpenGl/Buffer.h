#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>

class Buffer
{
public:
	Buffer();
	~Buffer();
	
	GLuint getBuffer();
private:
	GLuint bufferObject;
};
