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
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

	// Create vertex buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Setup attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, // shader attribute index
		2, // num components for attribute
		GL_FLOAT, // type used for attribute
		GL_FALSE, // 
		sizeof(float) * 2, // byte offset to hop
		0 // offset for attribute we're interested in
	);

	// Create index buffer object
	unsigned int indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
	
	OpenGLDebug::Enable();

	callbackService.Start();
}

Window::~Window()
{
	glDeleteProgram(shaderID);
	Stop();
}

void Window::Render()
{
	// Clear
	glClear(GL_COLOR_BUFFER_BIT);

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
