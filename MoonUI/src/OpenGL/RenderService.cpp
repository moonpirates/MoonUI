#include "RenderService.h"

RenderService::RenderService() :
	window(nullptr), renderer()
{

}

RenderService::~RenderService()
{
	renderer.Shutdown();
}

Renderer* RenderService::GetRenderer()
{
	if (!GLFW::IsInitialized || !GLEW::IsInitialized)
	{
		LOG_ERROR("Please initialize GLFW and GLEW first.");
		return nullptr;
	}

	if (!renderer.IsInitialized)
	{
		renderer.Init();
	}

	return &renderer;
}
