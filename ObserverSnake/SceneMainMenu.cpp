#include "SceneMainMenu.h"
#include "SceneStateMachine.h"
#include "Menu.h"
#include <functional>

SceneMainMenu::SceneMainMenu(SceneStateMachine& sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneMainMenu::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf = stateInf;
}

void SceneMainMenu::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneMainMenu::OnCreate()
{
	mainMenu = new Menu(
		{ L"Single player", L"Two players", L"Shop" },
		std::bind(
			[this](unsigned int listitem) {
				switch (listitem) {
				case 0: 
					SwitchTo("SinglePlayerScene");
					break;
				case 1:
					SwitchTo("TwoPlayerScene");
					break;
				case 2: 
					SwitchTo("ShopScene");
					break;
				}
			},
			std::placeholders::_1
		)
	);
}

void SceneMainMenu::OnActivate() {
	mainMenu->OnActivate();
}

void SceneMainMenu::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneMainMenu::Update() {
	mainMenu->ProcessInput();
}

void SceneMainMenu::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}
