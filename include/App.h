#ifndef APP_H
#define APP_H
#include "Graphics.h"
#include "GameState.h"

class App
{
public:
    App() = default;
    ~App() = default;

    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
    GameState* getGameState() { return gameState; }

private:
    bool running = false;
    GameState* gameState;

};

#endif