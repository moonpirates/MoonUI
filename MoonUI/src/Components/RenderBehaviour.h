#pragma once
#include "Systems/Components/Behaviour.h"

class RenderBehaviour : public Utils::Behaviour
{
public:
	RenderBehaviour();

protected:
	Renderer* renderer;
};

