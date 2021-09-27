#pragma once

#include <GLFW/glfw3.h>
#include "Systems/Components/Behaviour.h"

class Canvas : public Utils::Behaviour
{
public:
	Canvas();
	~Canvas();
	void Render() override;
};

