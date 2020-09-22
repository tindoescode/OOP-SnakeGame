#include "SceneLoadGame.h"
#include <filesystem>
#include <sstream>

// Constructor de khi tao mot SceneLoadGame o Game.cpp
SceneLoadGame::SceneLoadGame(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), gameOverMenu(nullptr) {}

// Cai nay de de~ dang nhan du lieu scene o Game.cpp
void SceneLoadGame::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneLoadGame::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

// Khi no duoc tao ra, ham nay chay cung voi constructor
void SceneLoadGame::OnCreate()
{
	auto path = std::filesystem::current_path();
	auto savegamePath = path;
	savegamePath += "\\savegames";

	std::filesystem::create_directory(savegamePath);

	// Top message
	Console::gotoXY(0, 0);
	Console::TextColor(ColorCode_Cyan);
	std::cout << "Choose a previous saved game to continue your progress." << std::endl;

	//
	std::vector<std::wstring> writer;

	for (const auto& entry : std::filesystem::directory_iterator(savegamePath)) {
		writer.push_back(entry.path().c_str());
	}
	writer.push_back(L"Back to main menu");

	// show menu that allow player to choose saved game file.
	gameOverMenu = new Menu(
		writer,
		std::bind(
			[this](unsigned int listitem, std::vector<std::wstring> writer) {
				if (listitem == writer.size()) {
					// Back to main menu
					_sceneStateMachine.SwitchTo(0);
				}
				else {
					//load	
				}
			},
			std::placeholders::_1, writer
		)
	);
}

// Con may cai nay phai co de handle action cua menu
void SceneLoadGame::OnActivate() {
	gameOverMenu->OnActivate();
}

void SceneLoadGame::OnDeactivate()
{
	// Clear map
	gameOverMenu->OnDeactivate();
}

void SceneLoadGame::ProcessInput() {
	gameOverMenu->ProcessInput();
}

void SceneLoadGame::OnDestroy()
{
	// Clear map
	gameOverMenu->OnDeactivate();

	delete gameOverMenu;
}
