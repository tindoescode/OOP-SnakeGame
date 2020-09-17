#pragma once
#include "Scene.h"
#include "Menu.h"
#include "SceneStateMachine.h"

class Object;
class SeceneGame;


static int NumOfSaves = 0;

class SceneSaveGame :
	public Scene
{
	friend class SceneStateMachine;
	friend class ScenePause;
public:
	SceneSaveGame(SceneStateMachine& sceneStateMachine);
	void SetSaveScene(std::shared_ptr<Scene>& prev);
	// Called when scene initially created. Called once.
	virtual void OnCreate();

	void OnActivate() override;

	// Called when scene destroyed. Called at most once (if a scene 
	// is not removed from the game, this will never be called).
	virtual void OnDestroy();

	void SetSwitchToScene(std::unordered_map<std::string, std::shared_ptr<Scene>> stateInf);
	void SwitchTo(std::string mapName);

private:
	// We want to go back to pauseScene after saving data
	std::shared_ptr<SceneGame> _saveScene;
	SceneStateMachine& _sceneStateMachine;
	std::unordered_map<std::string, std::shared_ptr<Scene>> _stateInf;
	
	
};