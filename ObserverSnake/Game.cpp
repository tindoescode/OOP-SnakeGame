#include "Game.h"
#include "SceneGame.h"

Game::Game() : running(true)
{
	std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();

	unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
	
	//TODO: Make splash screen scene
	//splashScense.setSwitchTo(gameSceneID)

	sceneStateMachine.SwitchTo(gameSceneID);
}

void Game::ProcessInput()
{
	sceneStateMachine.ProcessInput();
}

void Game::Update()
{
	sceneStateMachine.Update();
}

void Game::Draw()
{
	sceneStateMachine.Draw();
}

bool Game::IsRunning() const
{
	return running;
}
