#include "RenderService.h"

RenderService::RenderService()
{
	renderer.Init();
}

RenderService::~RenderService()
{
	renderer.Shutdown();
}

Renderer& RenderService::GetRenderer()
{
	return renderer;
}
