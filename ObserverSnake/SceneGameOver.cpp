#include "SceneGameOver.h"
#include "Game.h"

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
	gameOverMenu = new Menu(
		{ L"Yes", L"Exit" },
		std::bind(
			[this](unsigned int listitem) {
				switch (listitem) {
				case 0:
					// Play again, switch to scene choose map
					SwitchTo("SceneGame");  // roi bay gio t truyen SceneChooseMap voi Id cua no vao
					//SwitchTo cua sceneStateMachine nhan Id hoac nhan tham chieu cua scene can chuyen

					break;
				case 1:
					// Exit
					exit(false);
					break;
				}
			},
			std::placeholders::_1
		)
	);
}

// Con may cai nay phai co de handle action cua menu
void SceneGameOver::OnActivate() {
	
	TextColor(ColorCode_Cyan);
	gotoXY(SCREEN_WIDTH / 2 - (9 / 2), SCREEN_HEIGHT / 4);
	std::wcout << L"GAME OVER" << std::endl;
	gotoXY(SCREEN_WIDTH / 2 - (28 / 2), SCREEN_HEIGHT / 4 + 1);
	std::wcout << L"DO YOU WANT TO PLAY AGAIN ?" << std::endl;
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
