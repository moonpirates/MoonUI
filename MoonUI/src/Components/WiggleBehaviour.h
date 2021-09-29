#pragma once

#include "Systems/Components/Behaviour.h"
#include "Math/Vector.h"

class WiggleBehaviour : public Utils::Behaviour
{
public:
	WiggleBehaviour();
	void Update() override;

private:
	bool originalPositionSet;
	Utils::Vector3 originalPosition;
};

