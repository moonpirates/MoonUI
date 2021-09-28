#pragma once

#include "RenderBehaviour.h"
#include "Colors/Color.h"

class ImageBehaviour : public RenderBehaviour
{
public:
	Utils::Color Color;

	ImageBehaviour();
	void Render() override;
};

