#pragma once
#include "../Components/Canvas.h"
#include "../Components/ImageBehaviour.h"
#include "Systems/Scenes/SceneService.h"
#include "Systems/Components/Transform.h"
#include "Colors/Color.h"

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
		image->Color = Utils::Color::DarkGrey;
		Transform* transform = backgroundGO->GetComponent<Transform>();

		transform->Position = { 0, 0 };
		transform->Size = { 1280, 720};

		scene->PrintHierarchy();
	}
};

