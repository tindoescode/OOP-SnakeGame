#pragma once
#include "Scene.h"
#include <vector>

class MainMenu;
class SceneStateMachine;

class SceneChooseMap : public Scene
{
private:
	MainMenu* mainMenu;
	SceneStateMachine& _sceneStateMachine;

	std::vector<unsigned int> _stateIds;

public:
	SceneChooseMap(SceneStateMachine &sceneStateMachine);

	void SetSwitchToScene(std::vector<unsigned int> stateIds);
	void SwitchTo(unsigned int destinate);

	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void Update() override;
	void OnDestroy() override;
};

