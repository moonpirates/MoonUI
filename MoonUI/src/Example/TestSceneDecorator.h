#pragma once
#include "../Components/Canvas.h"
#include "../Components/ImageBehaviour.h"
#include "Systems/Scenes/SceneService.h"
#include "Systems/Components/Transform.h"
#include "Colors/Color.h"
#include "Math/Math.h"
#include "../Components/WiggleBehaviour.h"

using namespace Utils;

class TestSceneDecorator
{
public:
	TestSceneDecorator()
	{
		SceneService sceneService = GlobalServiceLocator::Get<SceneService>();

		Utils::Scene* scene = sceneService.LoadScene();

		GameObject* canvasGO = scene->AddGameObject("Canvas");
		canvasGO->AddComponent<Canvas>();

		GameObject* backgroundGO = canvasGO->AddChild("Background");
		ImageBehaviour* image = backgroundGO->AddComponent<ImageBehaviour>();
		image->Color = Utils::Color::Black;

		Transform* backgroundTransform = backgroundGO->GetComponent<Transform>();
		backgroundTransform->Position = { 0, 0 };
		backgroundTransform->Size = { 1280, 720 };

		float numTilesWidth = backgroundTransform->Size.X / tileSize.X;
		float numTilesHeight = backgroundTransform->Size.Y / tileSize.Y;

		for (size_t y = 0; y < numTilesHeight; y++)
		{
			for (size_t x = 0; x < numTilesWidth; x++)
			{
				auto pair = AddImage(backgroundGO, std::string("Image " + std::to_string(x) + ", " + std::to_string(y)));

				float tX = Math::InverseLerp(0, numTilesWidth, x);
				float tY = Math::InverseLerp(0, numTilesHeight, y);

				float r = Math::Lerp(0.25f, 1.0f, tX);
				float g = 0.0f;
				float b = Math::Lerp(1.0f, 0.25f, tY);

				pair.first->Color = { r, g, b, 1.0f };
				pair.first->TextureID = (x + y) % 2 == 0 ? 0 : 1;
				pair.second->Position = { x * tileSize.X + 1, y * tileSize.Y + 1 };
			}
		}

		//scene->PrintHierarchy();
	}

	std::pair<ImageBehaviour*, Transform*> AddImage(GameObject* parent, const std::string name)
	{
		GameObject* child = parent->AddChild(name);
		ImageBehaviour* image = child->AddComponent<ImageBehaviour>();
		//WiggleBehaviour* wiggle = child->AddComponent<WiggleBehaviour>();

		Transform* transform = child->GetComponent<Transform>();
		transform->Size = tileSize;

		return std::pair<ImageBehaviour*, Transform*> { image, transform };
	}
private:
	const Vector2 tileSize = { 64, 64 };
};

