#pragma once

#include "Services/BaseService.h"
#include "GLEW.h"
#include "GLFW.h"
#include "Renderer.h"

class RenderService : public Utils::BaseService
{
public:
	RenderService() = default;
	~RenderService();
	Renderer* GetRenderer();
	GLFWwindow* window;

private:
	Renderer renderer;
};