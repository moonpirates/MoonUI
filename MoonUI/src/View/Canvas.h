#pragma once

#include <Systems/Renderable.h>
#include <GLFW/glfw3.h>

class Canvas : public Utils::Renderable
{

public:
	Canvas();
	void Render() override;

};

