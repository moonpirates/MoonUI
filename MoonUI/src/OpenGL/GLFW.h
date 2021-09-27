#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFW
{

public:
	static bool TryInit()
	{
		// Initialize the library
		if (!glfwInit())
		{
			return false;
		}

		// Needed for OpenGL's debugger to attach
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	static GLFWwindow* TryCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
		
		if (!window)
		{
			glfwTerminate();
		}
		else
		{
			// Make the window's context current
			glfwMakeContextCurrent(window);

			GLFW::IsInitialized = true;
		}
	
		return window;
	}

	inline static bool IsInitialized;
};