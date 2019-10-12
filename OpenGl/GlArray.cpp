#include "GlArray.h"



GlArray::GlArray()
{
	glGenVertexArrays(1, &arrayObject);

	glBindVertexArray(arrayObject);
}
GlArray::~GlArray()
{

}

void GlArray::bindVertices(Buffer& vertexBuffer, float* vertices, GLenum usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.getBuffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, usage);
}
void::GlArray::bindIndices(Buffer& indexBuffer, unsigned int* indices, GLenum usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.getBuffer());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, usage);
}

GLuint GlArray::getArrayObject()
{
	return arrayObject;
}