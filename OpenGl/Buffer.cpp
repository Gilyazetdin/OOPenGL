#include "Buffer.h"

Buffer::Buffer()
{
	glGenBuffers(1, &bufferObject);	
}
Buffer::~Buffer()
{
}

GLuint Buffer::getBuffer()
{
	return bufferObject;
}