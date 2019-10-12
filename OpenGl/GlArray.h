#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>

#include "Buffer.h"

class GlArray 
{
public:
	GlArray();
	~GlArray();

	void bindVertices(Buffer& vertexBuffer, float* vertices, GLenum usage);
	void bindIndices(Buffer& indexBuffer, unsigned int* indices, GLenum usage);
	GLuint getArrayObject();
private:
	GLuint arrayObject;
};

