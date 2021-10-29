#include "ImageBehaviour.h"
#include "Systems/Components/Transform.h"

ImageBehaviour::ImageBehaviour() : Color(Utils::Color::White), TextureID(0)
{
}

void ImageBehaviour::Render()
{
	RenderBehaviour::Render();

	renderer->PushQuad(Transform->Position, Transform->Size, Color, TextureID);
}
