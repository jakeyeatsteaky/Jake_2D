#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "stdio.h"
template <typename T>
class Stack
{
public:
    Stack() : sp(nullptr), bp(nullptr), m_size(0) {}
    Stack(size_t size ): sp(new T[size]), bp(sp), m_size(size) {}
    ~Stack() {delete[] sp;}

    T* sp;
    T* bp;

    void push(T element);
    T pop();
    const T peek();
    bool isEmpty();
    bool isFull();

private:
    size_t m_size;
};

class Queue
{
public:
    Queue() : front(nullptr), back(nullptr), size(0) {};
    Queue(size_t size) : front(new int[size]), back(front), size(size) {}
    ~Queue() { delete[] front;}

    int* front;
    int* back;

    void push(const int element);
    int pop_front();
    const int peek_front();
    const bool isEmpty();
    const bool isFull();

private:
    size_t size;
};

class Vec3
{
public:
    Vec3() : xPos(0), yPos(0), zPos(0) {}
    Vec3(float x, float y, float z) : xPos(x), yPos(y), zPos(z) {}

    float DotProduct(Vec3& vec2);
    Vec3* CrossProduct(Vec3& vec2);
    float ScalarProjection(Vec3& vec1, Vec3& vec2);
    void printVec();

    Vec3& operator = (const Vec3& other);
    bool operator == (const Vec3& other);
    bool operator != (const Vec3& other);
    Vec3 operator + (const Vec3& other);
    Vec3 operator - (const Vec3& other);
    Vec3 operator * (const Vec3& other);
    Vec3 operator * (const float n);
    Vec3 operator / (const float n);
    Vec3 operator / (const Vec3& other);
    Vec3& operator += (const Vec3& other);
    Vec3& operator -= (const Vec3& other);
    Vec3& operator *= (const Vec3& other);
    Vec3& operator /= (const Vec3& other);

    float xPos; 
    float yPos; 
    float zPos; 
};

class Vec2
{
public:
    Vec2() = default;
    Vec2(float x, float y): xPos(x), yPos(y) {}
    ~Vec2() {}
    float xPos;
    float yPos;
};

struct Plane
{
    int A;
    int B;
    int C;
    int D;
};

/*
Implement a runtime code in C++ that sorts a 
list of game items based on their rarity. 
The items should be represented by a class with 
the following attributes: name (string), rarity (int), 
and value (float). The sorting should be performed 
using a custom comparator that compares the rarity of 
the items. Write a test program that creates a list of 
items and sorts them using your implementation.
*/

enum class Gem
{   
    Ruby,
    Jade,
    Sapphire
};

class GameItem
{
public:
    GameItem() = default;
    GameItem(Gem name, float value) : name(name), value(value) {
        calculateRarity(name, value, rarity);
    }
    ~GameItem(){}

    void calculateRarity(const Gem& name, const float value, int& rarity) {
        switch(name)
        {
            case Gem::Ruby:
                rarity = value * 10;
                break;
            case Gem::Jade:
                rarity = value * 5;
                break;
            case Gem::Sapphire:
                rarity = value *15;
                break;
            default:
                rarity = 0;
                break;
        }
    }

    Gem getName() const {return name;}
    int getRarity() const { return rarity;}
    float getValue() const {return value;}

private:
    Gem name;
    int rarity;
    float value;
};

void sortByRarity(std::vector<GameItem*>& item)
{
    std::vector<GameItem*>::iterator it = item.begin();
    std::vector<GameItem*>::iterator itEnd = item.end();

    std::sort(it, itEnd, [](GameItem* a, GameItem* b) {return a->getRarity() < b->getRarity();});
    
}

void testGameItemSort()
{
    GameItem* item1 = new GameItem(Gem::Jade, 15);
    GameItem* item2 = new GameItem(Gem::Ruby, 2.5);
    GameItem* item3 = new GameItem(Gem::Jade, 4.3);
    GameItem* item4 = new GameItem(Gem::Sapphire, 1.1);
    GameItem* item5 = new GameItem(Gem::Ruby, 2.0);
    GameItem* item6 = new GameItem(Gem::Jade, 2.5);
    GameItem* item7 = new GameItem(Gem::Jade, 7);
    GameItem* item8 = new GameItem(Gem::Ruby, 5.4);
    GameItem* item9 = new GameItem(Gem::Jade, 2.4);
    GameItem* item0 = new GameItem(Gem::Sapphire, 10);

    std::vector<GameItem*> gameItems = {item0, item1, item3, item2, item5, item6, item7, item8, item4, item9};
    
    for(auto items : gameItems)
    {
        std::cout << items->getRarity() << std::endl;
    }
    std::cout << "---------\n";

    sortByRarity(gameItems);

    for(auto items : gameItems)
    {
        std::cout << items->getRarity() << std::endl;
        delete items;
    }
}

#endif