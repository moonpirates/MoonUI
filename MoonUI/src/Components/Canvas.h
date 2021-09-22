#pragma once

#include <GLFW/glfw3.h>
#include <Systems/Renderable.h>

class Canvas : public Utils::Renderable
{
public:
	Canvas();
	~Canvas();
	void Render() override;
};

