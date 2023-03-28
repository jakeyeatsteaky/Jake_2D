#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <utility>
#include <memory>

#include "QuadTree.h"

class GameState
{
public:    
    GameState() = default;
    GameState(SDL_Rect activeArea): activeArea(activeArea), quadTree(nullptr), activePoints({}) {}
    
    ~GameState() = default;
    void addQuadTree(QuadTree* qt) { quadTree = qt;}
    void updateActivePoints() { activePoints = quadTree->query(activeArea); }
    void renderActive(uint32_t pointColor){ Graphics::DrawPoints(activePoints, pointColor);}

    QuadTree* getQuadTree() {return quadTree;}
    SDL_Rect getActiveArea() { return activeArea;}
    SDL_Rect activeArea;

private:
    QuadTree* quadTree;
    std::vector<Vec2<int>*> activePoints;

};

#endif
