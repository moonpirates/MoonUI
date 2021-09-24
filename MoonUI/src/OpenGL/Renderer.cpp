#include "Renderer.h"

void Renderer::Init()
{
	const int NUM_QUADS = 500; // hard coded max num quads
	const int NUM_VERTICES = NUM_QUADS * 4;
	const int NUM_INDICES = NUM_QUADS * 6;

	quadBuffer = new Vertex[NUM_VERTICES];
	quadBufferPointer = quadBuffer;

	// Create vertex buffer
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(sizeof(Vertex) * NUM_VERTICES);

	// Create vertex buffer layout
	VertexBufferLayout vertexBufferLayout = Vertex::GetVertexBufferLayout();
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);

	// Create index buffer object
	std::array<unsigned int, NUM_INDICES> indices = MeshGenerator::GetQuadIndices<NUM_INDICES>();
	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	// Create projection and view matrix
	projectionMatrix = new glm::mat4(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f));
	viewMatrix = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

	// Create shader program
	shader = new Shader("res/Shaders/Basic.shader");
	shader->Bind();

	// Create texture
	texture = new Texture("res/Textures/blisk-logo.png");
	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);

	vertexArray->Unbind();
	vertexBuffer->Unbind();
	indexBuffer->Unbind();
	shader->Unbind();
}

void Renderer::Shutdown()
{
	delete vertexArray;
	delete vertexBuffer;
	delete indexBuffer;
	delete shader;
	delete texture;
}

void Renderer::BeginBatch()
{

}

void Renderer::EndBatch()
{

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::PushQuad(const Utils::Vector2& position, const Utils::Vector2& size, const Utils::Vector4& color)
{
	auto quad = MeshGenerator::GetQuad(position.X, position.Y, size.X, size.Y);

	*quadBufferPointer = quad[0];
	quadBufferPointer++;
	*quadBufferPointer = quad[1];
	quadBufferPointer++;
	*quadBufferPointer = quad[2];
	quadBufferPointer++;
	*quadBufferPointer = quad[3];
	quadBufferPointer++;
}

void Renderer::Draw()
{
	// Set dynamic vertex buffer
	vertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0,  8 * sizeof(Vertex), quadBuffer);

	glm::mat4 modelMatrix = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	shader->Bind();
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetUniformMat4f("u_MVP", *projectionMatrix * *viewMatrix * modelMatrix);

	Clear();
	Draw(*vertexArray, *indexBuffer, *shader);
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}


