#pragma once
#include <array>
#include "Vertexh.h"

class MeshGenerator
{
public:
	static std::array<Vertex, 4> GetQuad(float x, float y, float width, float height);
	static std::array<int, 6> GetQuadIndices(int index);
};

