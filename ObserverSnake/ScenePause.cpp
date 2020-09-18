#include "ScenePause.h"
#include "SceneSaveGame.h"

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

void ScenePause::SwitchTo(std::shared_ptr<Scene> scene)
{
	_sceneStateMachine.SwitchTo(scene);
}

void ScenePause::OnCreate()
{
	pauseMenu = new Menu(
		{ "Continue", "Save game", "Load game", "Return to choose map", "Exit" },
		std::bind(
			[](unsigned int listitem, Scene* scene) {
				auto _this = dynamic_cast<ScenePause*>(scene);
				auto continueScene = _this->continueScene;
				
				switch (listitem) {
				case 0: {
					auto lastGameScene = continueScene;

					_this->_sceneStateMachine.SwitchTo(lastGameScene);
					break;
				}
				case 1: {
					std::shared_ptr<SceneSaveGame> saveGameScene 
						= std::make_shared<SceneSaveGame>(_this->_sceneStateMachine);

					saveGameScene->SetSwitchToScene({ 
						{ "ContinueScene", continueScene } 
					});

					//_this->_currentGameScene = saveGameScene;
					//_this->_currentGameScene->SetSaveGameScene(continueScene);

					saveGameScene->SetSaveGameScene(continueScene);

					_this->SwitchTo(saveGameScene);
					break;
				}
				case 2: {
					_this->SwitchTo("LoadGame");
					break;
				}
				case 3: {
					continueScene->OnCreate(); // reset old game sence when switching to choose map scene
					_this->SwitchTo("ChooseMapScene");
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
