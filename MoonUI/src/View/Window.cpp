#include "Window.h"

Window::Window() : 
	window(nullptr), windowWidth(0), windowHeight(0), callbackService(Utils::GlobalServiceLocator::Get<Utils::CallbackService>())
{
	callbackService.AddRenderable(*this);

	// Initialize the library
	if (!glfwInit())
	{
		return;
	}

	// Needed for OpenGL's debugger to attach
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(1280, 720, "Hello MoonUI!", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	UpdateWindowSize();

	// Make the window's context current
	glfwMakeContextCurrent(window);

	GLenum glInitResult = glewInit();
	if (glInitResult != GLEW_OK)
	{
		LOG_ERROR("Could not init GLEW.");
		glfwTerminate();
		return;
	}

	LOG("Initialized!");
	LOG(glGetString(GL_VERSION));

	unsigned int indices[] =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create vertex buffer
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(sizeof(Vertex) * 1000); // hard coded to a max of 1000 vertices

	// Create vertex buffer layout
	VertexBufferLayout vertexBufferLayout = Vertex::GetVertexBufferLayout();
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);

	// Create index buffer object
	indexBuffer = new IndexBuffer(indices, 12);

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

	renderer = new Renderer();

	OpenGLDebug::Enable();

	callbackService.Start();
}

Window::~Window()
{
	delete vertexArray;
	delete vertexBuffer;
	delete indexBuffer;
	delete shader;
	delete texture;
	delete renderer;

	Stop();
}

void Window::PreRender()
{

}

void Window::Render()
{
	UpdateWindowSize();

	auto quadA = MeshGenerator::GetQuad(200, 400, 100, 100);
	auto quadB = MeshGenerator::GetQuad(300, 200, 50, 300);

	Vertex vertices[8];
	memcpy(vertices, quadA.data(), quadA.size() * sizeof(Vertex));
	memcpy(vertices + quadA.size(), quadB.data(), quadB.size() * sizeof(Vertex));

	// Set dynamic vertex buffer
	vertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	renderer->Clear();

	shader->Bind();
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	
	glm::mat4 modelMatrix = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	shader->SetUniformMat4f("u_MVP", *projectionMatrix * *viewMatrix * modelMatrix);
	
	renderer->Draw(*vertexArray, *indexBuffer, *shader);

	// Swap front and back buffer
	glfwSwapBuffers(window);

	// Poll for events
	glfwPollEvents();

	// Wrap things up if we close the window
	if (glfwWindowShouldClose(window))
	{
		std::cout << "Bye!" << std::endl;
		Stop();
	}
}

void Window::Stop()
{
	glfwTerminate();
	callbackService.Stop();
}

void Window::UpdateWindowSize()
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

int Window::GetWindowWidth()
{
	return windowWidth;
}

int Window::GetWindowHeight()
{
	return windowHeight;
}
