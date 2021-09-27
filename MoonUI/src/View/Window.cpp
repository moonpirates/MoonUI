#include "Window.h"

Window::Window() : 
	window(nullptr), windowWidth(0), windowHeight(0), callbackService(Utils::GlobalServiceLocator::Get<Utils::CallbackService>()),
	renderer(Utils::GlobalServiceLocator::Get<RenderService>().GetRenderer())
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

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	OpenGLDebug::Enable();
}

Window::~Window()
{
	Stop();
}

void Window::PreRender()
{
	renderer.Clear();
	renderer.BeginBatch();
}

void Window::Render()
{
	UpdateWindowSize();

	renderer.PushQuad({ 0, 0 }, { 100, 100 }, { 1.0f, 1.0f, 1.0f, 1.0f, });
	renderer.PushQuad({ 200, 300 }, { 200, 50 }, { 1.0f, 1.0f, 1.0f, 1.0f, });
	renderer.PushQuad({ 400, 400 }, { 50, 50 }, { 1.0f, 1.0f, 1.0f, 1.0f, });

	// Poll for events
	glfwPollEvents();

	// Wrap things up if we close the window
	if (glfwWindowShouldClose(window))
	{
		std::cout << "Bye!" << std::endl;
		Stop();
	}
}

void Window::PostRender()
{
	renderer.EndBatch();

	// Swap front and back buffer
	glfwSwapBuffers(window);
}

void Window::Start()
{
	callbackService.Start();
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
