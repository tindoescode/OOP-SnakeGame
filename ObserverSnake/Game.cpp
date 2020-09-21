#include "Game.h"
#include "SceneChooseMap.h"
#include "SceneMainMenu.h"

Game::Game() : running(true)
{
	std::shared_ptr<SceneMainMenu> mainMenuScene = std::make_shared<SceneMainMenu>(sceneStateMachine);

	// Managing scene is hard, but manage its ID is a bit easier
	unsigned int mainMenuSceneID1 = sceneStateMachine.Add(mainMenuScene);

	sceneStateMachine.SwitchTo(mainMenuSceneID1);
}

void Game::ProcessInput()
{
	//Process Input by default
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
