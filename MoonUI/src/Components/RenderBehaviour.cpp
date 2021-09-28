#include "RenderBehaviour.h"

RenderBehaviour::RenderBehaviour()
{
	renderer = Utils::GlobalServiceLocator::Get<RenderService>().GetRenderer();
}
