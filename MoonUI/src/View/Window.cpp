#include "Window.h"

Window::Window() : window(nullptr), callbackService(Utils::GlobalServiceLocator::Get<Utils::CallbackService>())
{
	callbackService.AddRenderable(*this);

	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	
	if (err != GLEW_OK)
	{
		LOG_ERROR("Could not init GLEW.");
	}

	callbackService.Start();
}

Window::~Window()
{
	
}

void Window::Render()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();

	if (glfwWindowShouldClose(window))
	{
		std::cout << "Doei" << std::endl;
		glfwTerminate();
		callbackService.Stop();
	}
}
