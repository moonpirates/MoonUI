#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Macros/Macros.h"

class GLEW
{
public:
	static bool TryInit()
	{
		GLenum glInitResult = glewInit();
		if (glInitResult != GLEW_OK)
		{
			LOG_ERROR("Could not init GLEW.");
			glfwTerminate();
			return false;
		}

		IsInitialized = true;
		return true;
	}

	inline static bool IsInitialized;
};