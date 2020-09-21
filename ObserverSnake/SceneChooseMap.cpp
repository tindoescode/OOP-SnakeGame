#include "SceneChooseMap.h"
#include "SceneStateMachine.h"
#include "Menu.h"
#include <functional>

SceneChooseMap::SceneChooseMap(SceneStateMachine &sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneChooseMap::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf = stateInf;
}

void SceneChooseMap::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);
	
	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneChooseMap::OnCreate()
{
	mainMenu = new Menu(
		{ L"Classic Map 1", L"Classic Map 2", L"Modern Map 1", L"Modern Map 2", L"Shop" }, 
		std::bind(
			[this](unsigned int listitem) {
				switch (listitem) {
				case 0: {
					SwitchTo("ClassicMap1");
					break;
				}
				case 1: {
					SwitchTo("ClassicMap2");
					break;
				}
				case 2: {
					SwitchTo("ModernMap1");
					break;
				}
				case 3: {
					SwitchTo("ModernMap2");
					break;
				}
				case 4: {
					SwitchTo("ShopScene");
					break;
				}
				}

				//TextColor(ColorCode_White);
				//gotoXY(0, 0);
				//std::cout << "Select item: " << listitem << std::endl;
			},
			std::placeholders::_1
		)
	);
}

void SceneChooseMap::OnActivate() {
	 mainMenu->OnActivate();
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
