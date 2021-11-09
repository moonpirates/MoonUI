#include "ImageBehaviour.h"
#include "Systems/Components/Transform.h"

ImageBehaviour::ImageBehaviour() : Color(Utils::Color::White), TexturePath("")
{
}

void ImageBehaviour::Render()
{
	RenderBehaviour::Render();

	renderer->PushQuad(Transform->Position, Transform->Size, Color, TexturePath);
}
