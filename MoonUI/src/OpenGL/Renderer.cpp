#include "Renderer.h"

void Renderer::Init()
{
	if (IsInitialized)
	{
		LOG_WARN("Tried to init renderer twice.");
		return;
	}

	quadBuffer = new Vertex[MAX_NUM_VERTICES];
	quadBufferPointer = nullptr;

	// Create vertex buffer
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(sizeof(Vertex) * MAX_NUM_VERTICES);

	// Create vertex buffer layout
	VertexBufferLayout vertexBufferLayout = Vertex::GetVertexBufferLayout();
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);

	// Create index buffer object
	std::array<unsigned int, MAX_NUM_INDICES>* indices = MeshGenerator::GetQuadIndices<MAX_NUM_INDICES>();
	indexBuffer = new IndexBuffer(indices->data(), indices->size());
	delete indices;

	// Create projection and view matrix
	projectionMatrix = new glm::mat4(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f));
	viewMatrix = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

	// Create shader program
	shader = new Shader("res/Shaders/Basic.shader");
	shader->Bind();

	// Create texture
	textureBlisk = new Texture("res/Textures/blisk-logo.png");
	textureGithub = new Texture("res/Textures/github-logo.png");
	
	// Texture slots match indices in sampler array
	textureBlisk->Bind(0);
	textureGithub->Bind(1);
	
	int samplers[32];
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}

	shader->SetUniform1iv("u_Textures", 32, samplers);

	vertexArray->Unbind();
	vertexBuffer->Unbind();
	indexBuffer->Unbind();
	shader->Unbind();

	IsInitialized = true;
}

void Renderer::Shutdown()
{
	if (!IsInitialized)
	{
		LOG_WARN("Has not yet been initialized.");
		return;
	}

	vertexArray->Unbind();
	vertexBuffer->Unbind();
	indexBuffer->Unbind();
	shader->Unbind();

	quadBufferPointer = nullptr;

	delete vertexArray;
	delete vertexBuffer;
	delete indexBuffer;
	delete shader;
	delete textureBlisk;
	delete[] quadBuffer;

	IsInitialized = false;
}

void Renderer::BeginBatch()
{
	quadCount = 0;
	quadBufferPointer = quadBuffer;
}

void Renderer::EndBatch()
{
	Flush();
}

void Renderer::Flush()
{
	// Set dynamic vertex buffer
	vertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, quadCount * 4 * sizeof(Vertex), quadBuffer);

	glm::mat4 modelMatrix = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	shader->Bind();
	shader->SetUniformMat4f("u_MVP", *projectionMatrix * *viewMatrix * modelMatrix);

	Draw(*vertexArray, *indexBuffer, *shader);

	drawCount++;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawCount = 0;
}

void Renderer::PushQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Color& color, const float textureID)
{
	if (quadCount + 1 > MAX_NUM_QUADS)
	{
		EndBatch();
		BeginBatch();
	}

	std::array<Vertex, 4> quad = MeshGenerator::GetQuad(position, size, color, textureID);

	*quadBufferPointer = quad[0];
	quadBufferPointer++;
	*quadBufferPointer = quad[1];
	quadBufferPointer++;
	*quadBufferPointer = quad[2];
	quadBufferPointer++;
	*quadBufferPointer = quad[3];
	quadBufferPointer++;

	quadCount++;
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);

	drawCount++;
}


