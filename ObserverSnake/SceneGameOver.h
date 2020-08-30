#pragma once
#include "Scene.h"

class SceneGameOver : public Scene
{
	void OnCreate();

	void OnDestroy();

	void OnActivate() override;

	// Called whenever a transition out of a scene occurs. 
	// Can be called many times in a typical game cycle.
	virtual void OnDeactivate() {};

	// The below functions can be overridden as necessary in our scenes.
	virtual void ProcessInput() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void Draw() {};
};

