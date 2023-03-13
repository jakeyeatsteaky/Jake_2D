#ifndef STACK_H
#define STACK_H

#include "stdio.h"
template <typename T>
class Stack
{
public:
    Stack() : sp(nullptr), bp(nullptr), m_size(0) {}
    Stack(size_t size ): sp(new T[size]), bp(sp), m_size(size) {}
    ~Stack() {}

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

#endif