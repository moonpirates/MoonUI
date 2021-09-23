#pragma once

#include <iostream>
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* data, size_t count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;

private:
	unsigned int indexBufferID;
	size_t count;
};

