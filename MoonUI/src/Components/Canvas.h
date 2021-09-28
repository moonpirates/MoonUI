#pragma once

#include "Systems/Components/Behaviour.h"

class Canvas : public Utils::Behaviour
{
public:
	Canvas();
	~Canvas();
	void Render() override;
};

