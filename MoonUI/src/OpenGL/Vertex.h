#pragma once

#include "VertexBufferLayout.h"
#include "Math/Vector.h"
#include "Colors/Color.h"

struct Vertex
{
	Utils::Vector3 Position;
	Utils::Vector2 TextureCoords;
	Utils::Color Color;
	//float TextureID;

	static VertexBufferLayout GetVertexBufferLayout()
	{
		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(3);
		vertexBufferLayout.Push<float>(2);
		vertexBufferLayout.Push<float>(4);
		//vertexBufferLayout.Push<float>(1);

		return vertexBufferLayout;
	}
};