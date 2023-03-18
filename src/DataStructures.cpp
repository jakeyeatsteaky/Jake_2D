#include "DataStructures.h"

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////             STACK             //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
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
    sp--;
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


/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////             QUEUE             //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void Queue::push(const int element) 
{
    if(isFull())
        return;
    *back = element;
    back++;
}

int Queue::pop_front()
{
    int* temp = front;
    int ret = *temp;
    while(temp != back) {
        int* temp2 = temp + 1;
        *temp = *temp2;
        temp++;
    }
    return ret;
}

const bool Queue::isEmpty() { return front == back;}
const bool Queue::isFull() { return back == front + sizeof(int)*size;}

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////             Vector            //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void Vec3::printVec()
{
    printf("xPos: %.2f\tyPos: %.2f\tzPos: %.2f\n", xPos, yPos, zPos);
}

float Vec3::DotProduct(Vec3& other)
{
    return (xPos * other.xPos) + (yPos * other.yPos) + (zPos * other.zPos);
}


Vec3* Vec3::CrossProduct(Vec3& vec2)
{
    //  i    j    k
    //  x1   y1   z1
    //  x2   y2   z2

    float newX = (yPos * vec2.zPos) - (zPos * vec2.yPos);
    float newY = (xPos * vec2.zPos) - (zPos * vec2.xPos);
    float newZ = (xPos * vec2.yPos) - (yPos * vec2.xPos);
    if(newY != 0)
        newY *= -1;

     return new Vec3(newX, newY, newZ);
    
}

// float Vec3::ScalarProjection(Vec3& vec1, Vec3& vec2)
// {
//     return 0.f;
// }

Vec3& Vec3::operator = (const Vec3& other){
    xPos = other.xPos;
    yPos = other.yPos;
    zPos = other.zPos;
    return *this;
}

bool Vec3::operator == (const Vec3& other)
{
    return xPos == other.xPos && yPos == other.yPos && zPos == other.zPos;
}

bool Vec3::operator != (const Vec3& other)
{
    return xPos != other.xPos && yPos != other.yPos && zPos != other.zPos;
}

Vec3 Vec3::operator + (const Vec3& other)
{
    // float newX = xPos + other.xPos;
    // float newY = yPos + other.yPos;
    // float newZ = zPos + other.zPos;

    // return new Vec3(newX, newY, newZ);
    Vec3 vec;
    return vec;
}

Vec3 Vec3::operator - (const Vec3& other)
{
    return Vec3(xPos - other.xPos, yPos - other.yPos, zPos - other.zPos);
}

// Vec3 Vec3::operator * (const Vec3& other)
// {
//     return Vec3 vec;
// }

// Vec3 Vec3::operator * (const float n)
// {
//     return Vec3 vec;
// }

// Vec3 Vec3::operator / (const float n)
// {

// }

// Vec3 Vec3::operator / (const Vec3& other)
// {

// }

// Vec3& Vec3::operator += (const Vec3& other)
// {

// }

// Vec3& Vec3::operator -= (const Vec3& other)
// {

// }

// Vec3& Vec3::operator *= (const Vec3& other)
// {

// }

// Vec3& Vec3::operator /= (const Vec3& other)
// {

// }

// bool Vec3::operator == (const Vec3& other)
// {

// }

