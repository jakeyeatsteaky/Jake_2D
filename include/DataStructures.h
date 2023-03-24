#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <cmath>


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
    void Normalize();
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

enum class Gem
{   
    Ruby,
    Jade,
    Sapphire
};

class GameItem
{
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

// void sortByRaritys(std::vector<GameItem*>& item)
// {
//     std::vector<GameItem*>::iterator it = item.begin();
//     std::vector<GameItem*>::iterator itEnd = item.end();
//     std::sort(it, itEnd, [](GameItem* a, GameItem* b) {return a->getRarity() < b->getRarity();});
// }

class Mat3
{
public:
    Mat3() = default;
    Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2) {
        data[0] = row0;
        data[1] = row1;
        data[2] = row2;
    }

    void printMatrix() {
        for(Vec3& row : data)
        {
            std::cout << row.xPos << " " << row.yPos << " " << row.zPos << "\n";
        }
        std::cout << "-------\n";
    }

    void transpose() {
        Vec3 newRow0;
        Vec3 newRow1;
        Vec3 newRow2;

        newRow0.xPos = data[0].xPos;
        newRow0.yPos = data[1].xPos;
        newRow0.zPos = data[2].xPos;
        
        newRow1.xPos = data[0].yPos;
        newRow1.yPos = data[1].yPos;
        newRow1.zPos = data[2].yPos;

        newRow2.xPos = data[0].zPos;
        newRow2.yPos = data[1].zPos;
        newRow2.zPos = data[2].zPos;

        data[0] = newRow0;
        data[1] = newRow1;
        data[2] = newRow2;
    }

    Vec3 getRow(int index) {return data[index];}

private:
    std::array<Vec3, 3> data;
};

class Vec4
{
public:
    Vec4() = default;
    Vec4(Vec3&& vec, float w) : vec(vec), wPos(w) {}
    ~Vec4() {}

    void printVec() { vec.printVec(); printf("\t%2f\n", wPos); }

    Vec3 vec;
    float wPos;
};

class Mat4
{
public:
    Mat4() = default;
    Mat4(const Vec4&& row0, const Vec4&& row1, const Vec4&& row2, const Vec4&& row3)
    {
        data[0] = row0;
        data[1] = row1;
        data[2] = row2;
        data[3] = row3;
    }
    ~Mat4() {}

    Vec4 getRow(size_t idx) { return data[idx]; }
    void Transpose();
    void printMat4();

private:
    std::array<Vec4, 4> data;

};

namespace Matrix
{
    Mat4 mat4Translate(Vec3&& translation);

    void Vec3Translate(Vec3& vec, Mat4& translationMatrix);

}

typedef struct TreeNode TreeNode;
struct TreeNode
{
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    ~TreeNode() {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

struct BTree
{
    BTree() : m_top(nullptr), m_count(0) {}
    BTree(TreeNode* top) : m_top(top), m_count(1) {}
    ~BTree() {}

    void InsertNode(int value);
    void InsertNode(TreeNode* node);
    TreeNode* FindNode(int value);
    void DeleteNode(int value);
    void PrintNodes();

    TreeNode* m_top;
    size_t m_count;

};

class BST
{
public:
    BST() : root(nullptr), count(0) {}
    BST(int value) : root(new TreeNode(value)), count(1) {}
    BST(TreeNode* node) : root(node), count(1) {}
    ~BST(){}

    void InsertNode(int value);
    void Traversal_InOrder(TreeNode* node);
    void Traversal_PreOrder(TreeNode* node);
    void Traversal_PostOrder(TreeNode* node);

    inline TreeNode* getRoot() { return root; }
    inline size_t getCount() { return count; }


private:
    TreeNode* root;
    size_t count;
};

struct Sphere
{
    Sphere() : cx(0), cy(0), cz(0), r(0) {}
    Sphere(float x, float y, float z, float r) : cx(x), cy(y), cz(z), r(r) {}
    ~Sphere() {}

    float cx;
    float cy;
    float cz;
    float r;
};

#endif