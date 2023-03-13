#include "Stack.h"

template <typename T>
void Stack<T>::push(T element) {
    if(isFull()) {
        printf("Stack Overflow\n");
        return;
    }
    *sp = element;
    sp++;
}

template <typename T>
T Stack<T>::pop() 
{
    if(isEmpty()) {
        printf("Stack Is empty\n");
        return -1;
    }
    sp--;+
    T ret = *sp;
    return ret;
}

template <typename T>
const T Stack<T>::peek() {
    T* temp = sp;
    temp--;
    T ret = *temp;
    return ret;
}

template <typename T>
bool Stack<T>::isEmpty() { return sp == bp; }

template <typename T>
bool Stack<T>::isFull() { return sp == (bp + sizeof(T)*m_size);}