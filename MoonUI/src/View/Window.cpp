#include "Window.h"

Window::Window() : window(nullptr), callbackService(Utils::GlobalServiceLocator::Get<Utils::CallbackService>())
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
	window = glfwCreateWindow(640, 480, "Hello MoonUI!", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return;
	}

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

	// Create position vertices and UV maps
	float positions[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, // bottom left
		0.5f, -0.5f, 1.0f, 0.0f, //bottom right
		0.5f, 0.5f, 1.0f, 1.0f, // top right
		-0.5f, 0.5f, 0.0f, 1.0f // top left
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create vertex buffer
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(positions, sizeof(positions));

	// Create vertex buffer layout
	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.Push<float>(2);
	vertexBufferLayout.Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);

	// Create index buffer object
	indexBuffer = new IndexBuffer(indices, 6);

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

void Window::Render()
{
	renderer->Clear();

	float red = (std::sin(Utils::TimeUtil::TimeSinceStart * 4) + 1) / 2;
	float green = (std::sin(Utils::TimeUtil::TimeSinceStart * 2.4f) + 1) / 2;
	float blue = (std::sin(Utils::TimeUtil::TimeSinceStart * 1) + 1) / 2;
	shader->Bind();
	shader->SetUniform4f("u_Color", red, green, blue, 1.0f);

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
