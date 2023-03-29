#include <iostream>

#include "App.h"
#include "QuadTree.h"
#include "SDL.h" 
#include "DataStructures.h"
#include "util.h"


bool App::IsRunning()
{
    return running;
}

void App::Setup()
{
    SeedRandom();
    running = Graphics::CreateSDLWindow();

    // Initialize Game State
    SDL_Rect activeArea = {350,350, 300, 100};
    SDL_Rect rect = {0, 0, Graphics::window_width, Graphics::window_height};
    gameState = new GameState(activeArea);
    gameState->addQuadTree(new QuadTree(rect, QuadTree::QT_CAP));

    for(int i = 0; i < 500; ++i){
        int x = GenerateRandom(0,400); 
        int y = GenerateRandom(0,400); 
        Vec2<int>* point = new Vec2<int>(x, y);
        gameState->getQuadTree()->insert(point);
    }
    for(int i = 0; i < 50; ++i){
        int x = GenerateRandom(0,800); 
        int y = GenerateRandom(0,800); 
        Vec2<int>* point = new Vec2<int>(x, y);
        gameState->getQuadTree()->insert(point);
    }

}

void App::Input()
{
   SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        getGameState()->activeArea.y -= 10;
                        break;
                    case SDLK_DOWN:
                        getGameState()->activeArea.h += 10;
                        break;
                    case SDLK_LEFT:
                        getGameState()->activeArea.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        getGameState()->activeArea.w += 10;
                        break;
                    case SDLK_SPACE:
                        getGameState()->activeArea = {400,400,100,100};
                        break;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            default:
                break;
        }
    }

}

void App::Update()
{
    int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - timePrevFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    float  deltaTime = (SDL_GetTicks() - timePrevFrame) / 1000.0f;
    if (deltaTime > 0.05)
        deltaTime = 0.05;
    timePrevFrame = SDL_GetTicks();

    getGameState()->updateActivePoints();

}

void App::Render()
{
    QuadTree* qt = getGameState()->getQuadTree();
    GameState* gs = getGameState();

    Graphics::ClearScreen(0xFF000000);

    qt->render(0xFF0000FF, 0x00FF00FF); 
    gs->renderActive(0xFFFFFFFF);
    Graphics::DrawRect(getGameState()->activeArea, 0x00FF00FF);

    Graphics::RenderFrame();

    
    SDL_GL_SwapWindow(Graphics::window);
}

void App::Destroy()
{

}
