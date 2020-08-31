#include "Game.h"
#include "SceneGame.h"
#include "SceneChooseMap.h"
#include "ScenePause.h"

std::shared_ptr<ScenePause> pauseScene;

Game::Game() : running(true)
{
	std::shared_ptr<SceneGame> gameScene1 = std::make_shared<SceneGame>("ClassicMap1.dat", sceneStateMachine);
	std::shared_ptr<SceneGame> gameScene2 = std::make_shared<SceneGame>("ClassicMap2.dat", sceneStateMachine);
	std::shared_ptr<SceneGame> gameScene3 = std::make_shared<SceneGame>("ModernMap1.dat", sceneStateMachine);
	std::shared_ptr<SceneGame> gameScene4 = std::make_shared<SceneGame>("ModernMap2.dat", sceneStateMachine);
	std::shared_ptr<SceneChooseMap> chooseMapScene = std::make_shared<SceneChooseMap>(sceneStateMachine);
	std::shared_ptr<ScenePause> pauseScene = std::make_shared<ScenePause>(sceneStateMachine);

	unsigned int gameSceneID1 = sceneStateMachine.Add(gameScene1);
	unsigned int gameSceneID2 = sceneStateMachine.Add(gameScene2);
	unsigned int gameSceneID3 = sceneStateMachine.Add(gameScene3);
	unsigned int gameSceneID4 = sceneStateMachine.Add(gameScene4);
	unsigned int chooseMapSceneID = sceneStateMachine.Add(chooseMapScene);
	unsigned int pauseSceneID = sceneStateMachine.Add(pauseScene);

	//TODO: Make splash screen scene
	//splashScense.setSwitchTo(gameSceneID)
	//sceneStateMachine.SwitchTo(gameSceneID1);

	chooseMapScene->SetSwitchToScene({
		{ "ClassicMap1", gameSceneID1 }, 
		{ "ClassicMap2", gameSceneID2 }, 
		{ "ModernMap1", gameSceneID3 }, 
		{ "ModernMap2", gameSceneID4 },
		{ "PauseScene", pauseSceneID }	
	});

	pauseScene->SetSwitchToScene({
		{ "ChooseMapScene", chooseMapSceneID},
		{ "PauseScene", pauseSceneID }
	});

	::pauseScene = pauseScene;

	sceneStateMachine.SwitchTo(chooseMapSceneID);
}

void Game::ProcessInput()
{
	//Handle ESC Key
	if (GetAsyncKeyState(VK_ESCAPE)) {
		pauseScene->SetContinueScene(sceneStateMachine.GetCurrentScene());
		sceneStateMachine.SwitchTo(5);
	}

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