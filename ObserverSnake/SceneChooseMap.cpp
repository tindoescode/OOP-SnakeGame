#include "SceneChooseMap.h"
#include "MainMenu.h"
#include "SceneStateMachine.h"

SceneChooseMap::SceneChooseMap(SceneStateMachine &sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneChooseMap::SetSwitchToScene(std::vector<unsigned int> stateIds)
{
	// Stores the id of the scene that we will transition to.
	_stateIds = stateIds;
}

void SceneChooseMap::SwitchTo(unsigned int destinate)
{
	_sceneStateMachine.SwitchTo(destinate);
}

void SceneChooseMap::OnCreate()
{
	mainMenu = new MainMenu({"Classic Map 1", "Classic Map 2", "Modern Map 1", "Modern Map 2"}, *this);
}

void SceneChooseMap::OnActivate() {
	// mainMenu.show();
}

void SceneChooseMap::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneChooseMap::Update() {
	mainMenu->ProcessInput();
}

void SceneChooseMap::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}
