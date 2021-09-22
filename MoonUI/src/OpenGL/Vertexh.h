#pragma once

#include "VertexBufferLayout.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

struct Vertex
{
	Utils::Vector3 Position;
	//Utils::Vector2 Positions;
	//Utils::Vector4 Color;
	Utils::Vector2 TextureCoords;
	//float TextureID;

	static VertexBufferLayout GetVertexBufferLayout()
	{
		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(3);
		vertexBufferLayout.Push<float>(2);
		//vertexBufferLayout.Push<float>(3);
		//vertexBufferLayout.Push<float>(4);
		//vertexBufferLayout.Push<float>(2);
		//vertexBufferLayout.Push<float>(1);

		return vertexBufferLayout;
	}
};