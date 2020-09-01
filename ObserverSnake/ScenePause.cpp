#include "ScenePause.h"

ScenePause::ScenePause(SceneStateMachine& sceneStateMachine) 
	: Scene(), _sceneStateMachine(sceneStateMachine), pauseMenu(nullptr), continueScene(0) {}

void ScenePause::SetContinueScene(std::shared_ptr<Scene> &prev)
{
	continueScene = prev;
}

void ScenePause::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void ScenePause::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void ScenePause::OnCreate()
{
	pauseMenu = new Menu(
		{ "Continue", "Save game", "Load game", "Return to choose map", "Exit" },
		std::bind(
			[](unsigned int listitem, Scene* scene) {
				switch (listitem) {
				case 0: {
					dynamic_cast<ScenePause*>(scene)->_sceneStateMachine.SwitchTo(dynamic_cast<ScenePause*>(scene)->continueScene);
					break;
				}
				case 1: {
					dynamic_cast<ScenePause*>(scene)->SwitchTo("SaveGame");
					break;
				}
				case 2: {
					dynamic_cast<ScenePause*>(scene)->SwitchTo("LoadGame");
					break;
				}
				case 3: {
					dynamic_cast<ScenePause*>(scene)->SwitchTo("ChooseMapScene");
					break;
				}
				case 4: {
					exit(false);
					break;
				}
				}

				//TextColor(ColorCode_White);
				//gotoXY(0, 0);
				//std::cout << "Select item: " << listitem << std::endl;
			},
			std::placeholders::_1, (Scene*)this
		)
	);
}

void ScenePause::OnActivate() {
	pauseMenu->OnActivate();
}

void ScenePause::OnDeactivate()
{
	// Clear map
	pauseMenu->OnDeactivate();
}

void ScenePause::ProcessInput() {
	pauseMenu->ProcessInput();
}

void ScenePause::OnDestroy()
{
	// Clear map
	pauseMenu->OnDeactivate();

	delete pauseMenu;
}
