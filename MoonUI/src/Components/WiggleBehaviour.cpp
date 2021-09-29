#include "WiggleBehaviour.h"
#include "Systems/Components/Transform.h"

WiggleBehaviour::WiggleBehaviour() :
	originalPositionSet(false), originalPosition(Utils::Vector3::Zero)
{

}

void WiggleBehaviour::Update()
{
	if (!originalPositionSet)
	{
		originalPosition = Transform->Position;
		originalPositionSet = true;
	}

	float x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 1;
	float y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 1;

	Transform->Position = { originalPosition.X + x, originalPosition.Y + y };
}
