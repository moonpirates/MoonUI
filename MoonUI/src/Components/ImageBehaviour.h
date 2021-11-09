#pragma once

#include "RenderBehaviour.h"
#include "Colors/Color.h"

class ImageBehaviour : public RenderBehaviour
{
public:
	Utils::Color Color;
	std::string TexturePath;

	ImageBehaviour();
	void Render() override;
};

