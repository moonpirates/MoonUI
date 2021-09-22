#pragma once

#include <iostream>
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;

private:
	unsigned int indexBufferID;
	unsigned int count;
};

