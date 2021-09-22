#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();

	const auto& elements = vertexBufferLayout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexArrayAttrib(vertexBuffer.GetVertexBufferID(), i);
		glVertexAttribPointer(
			i, 
			element.Count, 
			element.Type, 
			element.Normalized, 
			vertexBufferLayout.GetStride(), 
			(const void*)offset);

		offset += element.Count * VertexBufferLayoutElement::GetSizeOfType(element.Type);

	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
