#include "SceneGameOver.h"

// Constructor de khi tao mot SceneGameOver o Game.cpp
SceneGameOver::SceneGameOver(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), gameOverMenu(nullptr) {}

// Cai nay de de~ dang nhan du lieu scene o Game.cpp
void SceneGameOver::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneGameOver::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

// Khi no duoc tao ra, ham nay chay cung voi constructor
void SceneGameOver::OnCreate()
{
	gotoXY(0, 0);
	TextColor(ColorCode_Cyan);
	std::cout << "Do you want to play again?" << std::endl;

	gameOverMenu = new Menu(
		{ "Yes", "Exit" },
		std::bind(
			[](unsigned int listitem, Scene* scene) {
				switch (listitem) {
				case 0:
					// Play again, switch to scene choose map
					dynamic_cast<SceneGameOver*>(scene)->SwitchTo("SceneChooseMap");  // roi bay gio t truyen SceneChooseMap voi Id cua no vao
					//SwitchTo cua sceneStateMachine nhan Id hoac nhan tham chieu cua scene can chuyen

					break;
				case 1:
					// Exit
					exit(false);
					break;
				}

				//TextColor(ColorCode_White);
				//gotoXY(0, 0);
				//std::cout << "Select item: " << listitem << std::endl;
			},
			std::placeholders::_1, (Scene*)this
		)
	);
}

// Con may cai nay phai co de handle action cua menu
void SceneGameOver::OnActivate() {
	gameOverMenu->OnActivate();
}

void SceneGameOver::OnDeactivate()
{
	// Clear map
	gameOverMenu->OnDeactivate();
}

void SceneGameOver::ProcessInput() {
	gameOverMenu->ProcessInput();
}

void SceneGameOver::OnDestroy()
{
	// Clear map
	gameOverMenu->OnDeactivate();

	delete gameOverMenu;
}
