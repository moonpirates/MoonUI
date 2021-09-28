#include "ImageBehaviour.h"
#include "Systems/Components/Transform.h"

ImageBehaviour::ImageBehaviour() : Color( { 1.0f, 1.0f, 1.0f, 1.0f })
{
}

void ImageBehaviour::Render()
{
	RenderBehaviour::Render();

	renderer->PushQuad(Transform->Position, Transform->Size, Color);
}
