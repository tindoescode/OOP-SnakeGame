#pragma once
#include "SceneStateMachine.h"

class Game
{
public:
    Game();

    void ProcessInput();
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;

private:
    SceneStateMachine sceneStateMachine; // New

    bool running;
};