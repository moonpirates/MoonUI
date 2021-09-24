#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Vertexh.h"
#include "Texture.h"
#include "MeshGenerator.h"

class Renderer
{
public:
	void Init();
	void Shutdown();

	void BeginBatch();
	void EndBatch();
	
	void Draw();
	void Clear() const;

	void PushQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Vector4& color);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Shader* shader;
	Texture* texture;
	glm::mat4* projectionMatrix;
	glm::mat4* viewMatrix;
	Vertex* quadBuffer;
	Vertex* quadBufferPointer;

	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};

