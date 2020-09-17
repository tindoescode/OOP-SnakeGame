#include "SceneSaveGame.h"
#include <fstream>
#include"SceneGame.h"

SceneSaveGame::SceneSaveGame(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), _saveScene(0){}

void SceneSaveGame::SetSaveScene(std::shared_ptr<Scene>& prev)
{
	_saveScene = std::dynamic_pointer_cast<SceneGame>(prev);
}

void SceneSaveGame::SetSwitchToScene(std::unordered_map<std::string, std::shared_ptr<Scene>> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneSaveGame::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneSaveGame::OnCreate()
{}
//std::shared_ptr<Scene>& ajshgdajhks(std::string a) {
	//return 
//}
void SceneSaveGame::OnActivate() 
{
	NumOfSaves++;
	std::string NameFile = "SaveGame" + std::to_string(NumOfSaves) + ".txt";
	std::ofstream writer(NameFile, std::ios::out);
	writer << _saveScene->getMapPath() << std::endl;
	writer << _saveScene->getFruit()->getX() << " " << _saveScene->getFruit()->getY() << std::endl;
	for (auto i : _saveScene->getSnake()->segments)
	{
		writer << i->getX() << " " << i->getY() << std::endl;
	}
	writer.close();
	gotoXY(30,10);
	TextColor(ColorCode_Cyan);
	std::cout << "Saving Game successfully";
	Sleep(1500);
	system("cls");
	_sceneStateMachine.SwitchTo(5);
}

void SceneSaveGame::OnDestroy()
{}
