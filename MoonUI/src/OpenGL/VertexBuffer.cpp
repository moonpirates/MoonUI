#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // size = sizeof(data)
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferID);
}

void VertexBuffer::Bind() const
{
	std::cout << "vertex bind: " << vertexBufferID << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
