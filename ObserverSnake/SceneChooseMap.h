#pragma once
#include "Scene.h"

class MainMenu;
class SceneStateMachine;

class SceneChooseMap : public Scene
{
private:
	MainMenu* mainMenu;
	SceneStateMachine& _sceneStateMachine;

	unsigned int switchToState;

public:
	SceneChooseMap(SceneStateMachine &sceneStateMachine);

	void SetSwitchToScene(unsigned int id);
	void SwitchTo();

	void OnCreate() override;
	void OnActivate() override;
	void OnDestroy() override;
};

