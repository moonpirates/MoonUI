#pragma once
#include "Services/BaseService.h"
#include "Renderer.h"

class RenderService : public Utils::BaseService
{
public:
	RenderService();
	~RenderService();
	Renderer& GetRenderer();

private:
	Renderer renderer;
};