#pragma once
#include "Systems/Components/Behaviour.h"

class ImageComponent : public Utils::Behaviour
{
public:
	void Update() override;
	void Render() override;

};

