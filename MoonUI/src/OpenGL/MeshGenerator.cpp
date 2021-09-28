#include "MeshGenerator.h"

std::array<Vertex, 4> MeshGenerator::GetQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Color& color)
{
	// Bottom left
	Vertex v0;
	v0.Position = position;
	v0.TextureCoords = { 0.0f, 0.0f };
	v0.Color = color;

	// Bottom right
	Vertex v1;
	v1.Position = { position.X + size.X, position.Y, 0.0f };
	v1.TextureCoords = { 1.0f, 0.0f };
	v1.Color = color;

	// Top right
	Vertex v2;
	v2.Position = { position.X + size.X, position.Y + size.Y, 0.0f };
	v2.TextureCoords = { 1.0f, 1.0f };
	v2.Color = color;

	// Top left
	Vertex v3;
	v3.Position = { position.X, position.Y + size.Y, 0.0f };
	v3.TextureCoords = { 0.0f, 1.0f };
	v3.Color = color;
	
	return { v0, v1, v2, v3 };
}

