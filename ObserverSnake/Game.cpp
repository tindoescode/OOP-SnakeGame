#include "Game.h"
#include "SceneGame.h"
#include "SceneChooseMap.h"
#include "ScenePause.h"
#include "SceneGameOver.h"
#include "SceneSaveGame.h"
#include"SceneShop.h"

Game::Game() : running(true)
{
	//std::shared_ptr<SceneGame> gameScene1 = std::make_shared<SceneGame>("ClassicMap1.dat", sceneStateMachine);
	//std::shared_ptr<SceneGame> gameScene2 = std::make_shared<SceneGame>("ClassicMap2.dat", sceneStateMachine);
	//std::shared_ptr<SceneGame> gameScene3 = std::make_shared<SceneGame>("ModernMap1.dat", sceneStateMachine);
	//std::shared_ptr<SceneGame> gameScene4 = std::make_shared<SceneGame>("ModernMap2.dat", sceneStateMachine);
	//std::shared_ptr<SceneChooseMap> chooseMapScene = std::make_shared<SceneChooseMap>(sceneStateMachine);
	//std::shared_ptr<ScenePause> pauseScene = std::make_shared<ScenePause>(sceneStateMachine);
	//std::shared_ptr<SceneGameOver> gameOverScene = std::make_shared<SceneGameOver>(sceneStateMachine);
	//std::shared_ptr<SceneShop> ShopScene = std::make_shared<SceneShop>(sceneStateMachine);

	//unsigned int gameSceneID1 = sceneStateMachine.Add(gameScene1);
	//unsigned int gameSceneID2 = sceneStateMachine.Add(gameScene2);
	//unsigned int gameSceneID3 = sceneStateMachine.Add(gameScene3);
	//unsigned int gameSceneID4 = sceneStateMachine.Add(gameScene4);
	//unsigned int chooseMapSceneID = sceneStateMachine.Add(chooseMapScene);
	//unsigned int pauseSceneID = sceneStateMachine.Add(pauseScene);
	//unsigned int gameOverSceneID = sceneStateMachine.Add(gameOverScene);
	//unsigned int ShopSceneID = sceneStateMachine.Add(ShopScene);

	//// These scenes need to know every scenes below
	//chooseMapScene->SetSwitchToScene({
	//	{ "ClassicMap1", gameSceneID1 }, 
	//	{ "ClassicMap2", gameSceneID2 }, 
	//	{ "ModernMap1", gameSceneID3 }, 
	//	{ "ModernMap2", gameSceneID4 },
	//	{ "PauseScene", pauseSceneID },
	//	{ "ShopScene", ShopSceneID }
	//});
	//ShopScene->SetSwitchToScene({
	//	{ "ChooseMapScene", chooseMapSceneID}
	//	});
	//pauseScene->SetSwitchToScene({
	//	{ "ChooseMapScene", chooseMapSceneID}
	//	// LoadScene
	//});

	//gameOverScene->SetSwitchToScene({
	//	{ "SceneChooseMap", chooseMapSceneID}
	//});

	//// Game scenes need to know pauseScene, when it want to switch scene
	//gameScene1->SetPauseScene(pauseScene);
	//gameScene2->SetPauseScene(pauseScene);
	//gameScene3->SetPauseScene(pauseScene);
	//gameScene4->SetPauseScene(pauseScene);

	//gameScene1->SetSwitchToScene({
	//	{ "SceneGameOver", gameOverSceneID},
	//	{ "PauseScene", pauseSceneID }
	//});
	//gameScene2->SetSwitchToScene({
	//	{ "SceneGameOver", gameOverSceneID},
	//	{ "PauseScene", pauseSceneID }
	//	});
	//gameScene3->SetSwitchToScene({
	//	{ "SceneGameOver", gameOverSceneID},
	//	{ "PauseScene", pauseSceneID }
	//});
	//gameScene4->SetSwitchToScene({
	//	{ "SceneGameOver", gameOverSceneID},
	//	{ "PauseScene", pauseSceneID }
	//});

	// Create scene
	std::vector<std::string> maps = { "ModernMap1.dat", "ModernMap2.dat", "ClassicMap1.dat", "ClassicMap2.dat" };

	std::shared_ptr<SceneGame> gameScene1 = std::make_shared<SceneGame>(maps, sceneStateMachine);
	std::shared_ptr<ScenePause> pauseScene = std::make_shared<ScenePause>(sceneStateMachine);
	std::shared_ptr<SceneGameOver> gameOverScene = std::make_shared<SceneGameOver>(sceneStateMachine);
	std::shared_ptr<SceneShop> ShopScene = std::make_shared<SceneShop>(sceneStateMachine);

	// Managing scene is hard, but manage its ID is a bit easier
	unsigned int gameSceneID1 = sceneStateMachine.Add(gameScene1);
	unsigned int pauseSceneID = sceneStateMachine.Add(pauseScene);
	unsigned int gameOverSceneID = sceneStateMachine.Add(gameOverScene);
	unsigned int ShopSceneID = sceneStateMachine.Add(ShopScene);

	// Game scenes need to know pauseScene, when pauseScene want to know current playing scene
	gameScene1->SetPauseScene(pauseScene);

	// Scene can be switched from game scene
	gameScene1->SetSwitchToScene({
		{ "SceneGameOver", gameOverSceneID},
		{ "PauseScene", pauseSceneID }
	});

	gameOverScene->SetSwitchToScene({
		{ "SceneGame", gameSceneID1}
	});

	sceneStateMachine.SwitchTo(gameScene1);
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
