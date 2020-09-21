#pragma once
#include "Scene.h"
#include <vector>
#include <unordered_map>
class Menu;
class SceneStateMachine;
const int startPositionName = 50;
const int startPositionRound = 60;
const int startPositionScore = 70;
class SceneScoreBoard : public Scene
{
private:
	Menu* mainMenu;
	SceneStateMachine& _sceneStateMachine;

public:
	SceneScoreBoard(SceneStateMachine& sceneStateMachine);

	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void Update() override;
	void OnDestroy() override;

	void DrawBorder();
};

