#pragma once

#include "Systems/Components/Behaviour.h"

class RenderComponent : public Utils::Behaviour
{
public:
	void Update() override;
	void Render() override;
};

