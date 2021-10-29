#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math/Vector.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"
#include "MeshGenerator.h"
#include "Colors/Color.h"

class Renderer
{
public:
	bool IsInitialized;
	
	void Init();
	void Shutdown();

	void BeginBatch();
	void EndBatch();
	
	void Flush();
	void Clear();

	void PushQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Color& color, const float textureID);

private:
	static const int MAX_NUM_QUADS = 1000; // Max number of quads per batch
	static const int MAX_NUM_VERTICES = MAX_NUM_QUADS * 4;
	static const int MAX_NUM_INDICES = MAX_NUM_QUADS * 6;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Shader* shader;
	Texture* textureBlisk;
	Texture* textureGithub;
	
	glm::mat4* projectionMatrix;
	glm::mat4* viewMatrix;
	
	Vertex* quadBuffer;
	Vertex* quadBufferPointer;
	uint32_t quadCount;
	uint32_t drawCount;

	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);
};

