#include "SceneChooseMap.h"
#include "MainMenu.h"
#include "SceneStateMachine.h"

SceneChooseMap::SceneChooseMap(SceneStateMachine &sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr), switchToState(0) {}

void SceneChooseMap::SetSwitchToScene(unsigned int id)
{
	// Stores the id of the scene that we will transition to.
	switchToState = id;
}

void SceneChooseMap::SwitchTo()
{
	_sceneStateMachine.SwitchTo(switchToState);
}

void SceneChooseMap::OnCreate()
{
	mainMenu = new MainMenu({"Map 1", "Map 2", "Map 3"}, *this);
}

void SceneChooseMap::OnActivate() {
	
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
