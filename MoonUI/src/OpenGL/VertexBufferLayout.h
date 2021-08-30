#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "VertexBufferLayoutElement.h"

class VertexBufferLayout
{
public:
	VertexBufferLayout() : stride(0)
	{
	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return elements; }
	inline const unsigned int GetStride() const { return stride; }

private:
	std::vector<VertexBufferLayoutElement> elements;
	unsigned int stride;
};

