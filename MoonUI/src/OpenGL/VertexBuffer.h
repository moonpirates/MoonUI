#pragma once

#include <iostream>
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	const unsigned int GetVertexBufferID() const;

private:
	unsigned int vertexBufferID;
};

