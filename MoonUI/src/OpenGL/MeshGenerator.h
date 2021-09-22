#pragma once
#include <array>
#include <vector>
#include "Vertexh.h"

class MeshGenerator
{
public:
	static std::array<Vertex, 4> GetQuad(float x, float y, float width, float height);
	static std::vector<unsigned int> GetQuadIndices(unsigned int quadIndexOffset, unsigned int numQuads);
};

