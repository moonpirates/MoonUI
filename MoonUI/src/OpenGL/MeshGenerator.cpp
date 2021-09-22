#include "MeshGenerator.h"

std::array<Vertex, 4> MeshGenerator::GetQuad(float x, float y, float width, float height)
{
	// Bottom left
	Vertex v0;
	v0.Position = { x, y, 0.0f };
	v0.TextureCoords = { 0.0f, 0.0f };

	// Bottom right
	Vertex v1;
	v1.Position = { x + width, y, 0.0f };
	v1.TextureCoords = { 1.0f, 0.0f };

	// Top right
	Vertex v2;
	v2.Position = { x + width, y + height, 0.0f };
	v2.TextureCoords = { 1.0f, 1.0f };

	// Top left
	Vertex v3;
	v3.Position = { x, y + height, 0.0f };
	v3.TextureCoords = { 0.0f, 1.0f };
	
	return { v0, v1, v2, v3 };
}

std::array<int, 6> MeshGenerator::GetQuadIndices(int index)
{
	return {
		0 * index,
		1 * index,
		2 * index,
		2 * index,
		3 * index,
		0 * index
	};
}
