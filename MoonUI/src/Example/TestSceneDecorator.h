#pragma once
#include "Systems/Scenes/SceneService.h"
#include "../Components/Canvas.h"
#include "../Components/ImageComponent.h"

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
		backgroundGO->AddComponent<ImageComponent>();

	}
};

