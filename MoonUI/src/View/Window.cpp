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

	// Create position vertices
	float positions[] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);

	// Create vertex buffer
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(positions, sizeof(positions));

	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);

	// Create index buffer object
	indexBuffer = new IndexBuffer(indices, 6);

	// Create shader program
	ShaderSource shaderSource = ShaderUtils::ParseShaderFile("res/Shaders/Basic.shader");
	shaderID = ShaderUtils::CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
	glUseProgram(shaderID);

	int location = glGetUniformLocation(shaderID, "u_Color");
	if (location == -1)
	{
		LOG_ERROR("Could not find uniform.");
		return;
	}
	glUniform4f(location, 0.2f, 0.3f, 0.9f, 1.0f);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	OpenGLDebug::Enable();

	callbackService.Start();
}

Window::~Window()
{
	delete vertexBuffer;
	delete indexBuffer;

	glDeleteProgram(shaderID);
	Stop();
}

void Window::Render()
{
	// Clear
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderID);
	float red = (std::sin(Utils::TimeUtil::TimeSinceStart * 4) + 1) / 2;
	float green = (std::sin(Utils::TimeUtil::TimeSinceStart * 2.4f) + 1) / 2;
	float blue = (std::sin(Utils::TimeUtil::TimeSinceStart * 1) + 1) / 2;
	int location = glGetUniformLocation(shaderID, "u_Color");
	glUniform4f(location, red, green, blue, 1.0f);

	vertexArray->Bind();
	indexBuffer->Bind();

	// Render num indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
