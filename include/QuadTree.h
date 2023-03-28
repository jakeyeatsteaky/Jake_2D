#ifndef QUADTREE_H
#define QUADTREE_H
#include "SDL.h"
#include "DataStructures.h"
#include "Graphics.h"

class QuadTree
{
public:
    static const int QT_CAP = 5;
    QuadTree() = default;
    QuadTree(SDL_Rect rect, size_t cap) : rect(rect), capacity(cap), isSubdivided(false) {}
    ~QuadTree(){}

    SDL_Rect getRect() {return rect;}
    bool getSubdivision() { return isSubdivided; }
    std::vector<QuadTree*> getQuadTrees() { return quadTrees; }
    std::vector<Vec2<int>*> getPoints() { return points;}

    void subdivide()
    {
        SDL_Rect nw_Rect = {rect.x, rect.y, rect.w/2, rect.h/2};
        SDL_Rect ne_Rect = {rect.x + rect.w/2, rect.y, rect.w/2, rect.h/2};
        SDL_Rect sw_Rect = {rect.x, rect.y + rect.h/2, rect.w/2, rect.h/2};
        SDL_Rect se_Rect = {rect.x + rect.w/2, rect.y + rect.h/2, rect.w/2, rect.h/2};

        QuadTree* NorthWest = new QuadTree(nw_Rect,QT_CAP);
        QuadTree* NorthEast = new QuadTree(ne_Rect,QT_CAP);
        QuadTree* SouthWest = new QuadTree(sw_Rect,QT_CAP);
        QuadTree* SouthEast = new QuadTree(se_Rect,QT_CAP);

        quadTrees.push_back(NorthWest);
        quadTrees.push_back(NorthEast);
        quadTrees.push_back(SouthWest);
        quadTrees.push_back(SouthEast);

        isSubdivided = true;
    }

    bool validPoint(Vec2<int>* point)
    {
        return (point->xPos > this->rect.x && 
                point->xPos < (this->rect.x + this->rect.w) &&
                point->yPos > this->rect.y &&
                point->yPos < (this->rect.y + this->rect.h));
    }

    bool pointWithinRange(Vec2<int>* point, SDL_Rect& range)
    {
        return (point->xPos > range.x && 
                point->xPos < (range.x + range.w) &&
                point->yPos > range.y &&
                point->yPos < (range.y + range.h));
    }

    void insert(Vec2<int>* point)
    {
        if(!validPoint(point))
            return;

        if(points.size() < capacity)
            points.push_back(point);

        else {
            if(!getSubdivision())
                subdivide();
            quadTrees[0]->insert(point);
            quadTrees[1]->insert(point);
            quadTrees[2]->insert(point);
            quadTrees[3]->insert(point);
        }
    }

    void render(uint32_t rectColor, uint32_t pointColor)
    {
        Graphics::DrawRect(rect, rectColor);
        Graphics::DrawPoints(points, pointColor);
        if(getSubdivision()) {
            for(QuadTree* qts : quadTrees)
                qts->render(rectColor, pointColor);
        }

    }

    bool intersects(SDL_Rect& range)
    {
        // if the logic in parentheses is true, they do NOT intersect
        return !(range.x > rect.x + rect.w ||
                 range.x + range.w < rect.x ||
                 range.y > rect.y + rect.h ||
                 range.y + range.h < rect.y);
    }

    std::vector<Vec2<int>*> query(SDL_Rect& range)
    {
        std::vector<Vec2<int>*> pointMap{};
        queryHelper(pointMap, range);
        return pointMap;
        
    }

    void queryHelper(std::vector<Vec2<int>*>& pointMap, SDL_Rect& range)
    {
        if(!intersects(range))
            return;

        for(Vec2<int>* point : points)
        {
            if(pointWithinRange(point, range))
                pointMap.push_back(point);
        }

        if(getSubdivision()) {
            quadTrees[0]->queryHelper(pointMap, range);
            quadTrees[1]->queryHelper(pointMap, range);
            quadTrees[2]->queryHelper(pointMap, range);
            quadTrees[3]->queryHelper(pointMap, range);
        }
    }


private:
    bool isSubdivided;
    SDL_Rect rect;
    size_t capacity;
    std::vector<Vec2<int>*> points;
    std::vector<QuadTree*> quadTrees;

};




#endif