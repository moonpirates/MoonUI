#pragma once

#include <iostream>
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;

private:
	unsigned int vertexBufferID;
};

