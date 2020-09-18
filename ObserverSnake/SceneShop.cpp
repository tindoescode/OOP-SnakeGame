#include "SceneStateMachine.h"
#include "Menu.h"
#include <functional>
#include"SceneShop.h"
SceneShop::SceneShop(SceneStateMachine& sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneShop::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf = stateInf;
}

void SceneShop::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneShop::OnCreate()
{
	mainMenu = new Menu(
		{ L"10 Score: Snake's Color is Red", 
		L"20 Score: Snake's Color is Blue", 
		L"30 Score: Snake's Color is Cyan", 
		L"20 Score: Snake's Speed x2",
		L"20 Score: Snake's Speed x3",
		L"Back to ChooseMapMenu" },
		std::bind(
			[](unsigned int listitem, Scene* scene) {
				switch (listitem) {
				case 0: {
					break;
				}
				case 1: {
					break;
				}
				case 2: {
					break;
				}
				case 3: {
					break;
				}
				case 4: {
					break;
				}
				case 5: {
					dynamic_cast<SceneShop*>(scene)->SwitchTo("ChooseMapScene");
					break;
				}
				}
			},
			std::placeholders::_1, (Scene*)this
				)
	);
}

void SceneShop::OnActivate() {
	mainMenu->OnActivate();
}

void SceneShop::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneShop::Update() {
	mainMenu->ProcessInput();
}

void SceneShop::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}
