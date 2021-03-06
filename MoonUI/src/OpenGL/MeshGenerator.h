#pragma once
#include <array>
#include <vector>
#include "Vertex.h"
#include "Colors/Color.h"
#include "Math/Vector.h"

class MeshGenerator
{
public:
	static std::array<Vertex, 4> GetQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Color& color);
	static std::array<Vertex, 4> GetQuad(const Utils::Vector2& position, const Utils::Vector2& size, const float& textureID);
	static std::array<Vertex, 4> GetQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Color& color, const float& textureID);

	template <int NumIndices>
	static std::array<unsigned int, NumIndices>* GetQuadIndices()
	{
		std::array<unsigned int, NumIndices>* indices = new std::array<unsigned int, NumIndices>();

		for (unsigned int i = 0; i < indices->size(); i += 6)
		{
			unsigned int offset = ((i / 6) * 4);

			(*indices)[i] = 0 + offset;
			(*indices)[i + 1] = 1 + offset;
			(*indices)[i + 2] = 2 + offset;
			(*indices)[i + 3] = 2 + offset;
			(*indices)[i + 4] = 3 + offset;
			(*indices)[i + 5] = 0 + offset;
		}

		return indices;
	}
};

