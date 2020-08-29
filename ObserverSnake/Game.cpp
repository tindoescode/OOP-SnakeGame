#include "Game.h"
#include "SceneGame.h"
#include "SceneChooseMap.h"

Game::Game() : running(true)
{
	std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>("ModernMap2.dat", sceneStateMachine);
	std::shared_ptr<SceneChooseMap> chooseMapScene = std::make_shared<SceneChooseMap>(sceneStateMachine);
	unsigned int chooseMapSceneID = sceneStateMachine.Add(chooseMapScene);
	unsigned int gameSceneID = sceneStateMachine.Add(gameScene);

	//TODO: Make splash screen scene
	//splashScense.setSwitchTo(gameSceneID)

	//sceneStateMachine.SwitchTo(gameSceneID);
	chooseMapScene->SetSwitchToScene(gameSceneID);
	sceneStateMachine.SwitchTo(chooseMapSceneID);
}

void Game::ProcessInput()
{
	sceneStateMachine.ProcessInput();
}

void Game::Update()
{
	sceneStateMachine.Update();
}

void Game::LateUpdate()
{
	sceneStateMachine.LateUpdate();
}

void Game::Draw()
{
	sceneStateMachine.Draw();
}

bool Game::IsRunning() const
{
	return running;
}
