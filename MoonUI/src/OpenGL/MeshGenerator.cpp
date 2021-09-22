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

std::vector<unsigned int> MeshGenerator::GetQuadIndices(unsigned int quadIndexOffset, unsigned int numQuads)
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < numQuads; i++)
	{
		unsigned int offset = 4 * (quadIndexOffset + i);
		indices.insert(indices.end(),
			{
				0 + offset,
				1 + offset,
				2 + offset,
				2 + offset,
				3 + offset,
				0 + offset
			});
	}

	return indices;
}
