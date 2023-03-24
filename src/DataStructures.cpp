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
    printf("xPos: %.2f\tyPos: %.2f\tzPos: %.2f", xPos, yPos, zPos);
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

void Vec3::Normalize()
{
    float magnitude = 1.f;//sqrt(magSquared());
    this->xPos /= magnitude;
    this->yPos /= magnitude;
    this->zPos /= magnitude;
}

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


void Mat4::Transpose()
{
    Vec4 newRow0;
    Vec4 newRow1;
    Vec4 newRow2;
    Vec4 newRow3;

    newRow0.vec.xPos = data[0].vec.xPos;
    newRow0.vec.yPos = data[1].vec.xPos;
    newRow0.vec.zPos = data[2].vec.xPos;
    newRow0.wPos = data[3].vec.xPos;
    
    newRow1.vec.xPos = data[0].vec.yPos;
    newRow1.vec.yPos = data[1].vec.yPos;
    newRow1.vec.zPos = data[2].vec.yPos;
    newRow1.wPos = data[3].vec.yPos;
    
    newRow2.vec.xPos = data[0].vec.zPos;
    newRow2.vec.yPos = data[1].vec.zPos;
    newRow2.vec.zPos = data[2].vec.zPos;
    newRow2.wPos = data[3].vec.zPos;

    newRow3.vec.xPos = data[0].wPos;
    newRow3.vec.yPos = data[1].wPos;
    newRow3.vec.zPos = data[2].wPos;
    newRow3.wPos = data[3].wPos;
    
    data[0] = newRow0;
    data[1] = newRow1;
    data[2] = newRow2;
    data[3] = newRow3;
}

void Mat4::printMat4() {
        for(Vec4 vec : data)
        {
            std::cout << vec.vec.xPos << " " << vec.vec.yPos << " " << vec.vec.zPos << " " << vec.wPos << "\n";
        }
        std::cout << "-----------\n";
}

Mat4 Matrix::mat4Translate(Vec3&& translation){
    const Vec4 row0 = Vec4(Vec3(1,0,0), 0);
    const Vec4 row1 = Vec4(Vec3(0,1,0), 0);
    const Vec4 row2 = Vec4(Vec3(0,0,1), 0);
    const Vec4 row3 = Vec4(std::move(translation), 1);
    
    return Mat4(std::move(row0), std::move(row1), std::move(row2), std::move(row3));
}

void Matrix::Vec3Translate(Vec3& vec, Mat4& translationMatrix)
{
    Vec4 vec4 = Vec4(std::move(vec), 1);
}

void BTree::PrintNodes()
{
    if(!m_top){
        return;
    }

    std::queue<TreeNode*> q;
    q.push(m_top);

    while(!q.empty())
    {
        TreeNode* current = q.front();
        q.pop();
        std::cout << current->val << std::endl;
        if(current->left)
            q.push(current->left);
        if(current->right)
            q.push(current->right);
    }
    std::cout << "Number of Nodes in this Tree: " << m_count << std::endl;
}

void BTree::InsertNode(TreeNode* node)
{
    // Check if root is empty;
    m_count++;
    if(!m_top){
        m_top = node;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(m_top);

    while(!q.empty())
    {
        TreeNode* current = q.front();
        q.pop();

        if(!current->left){
            current->left = node;
            return;
        }
        else
            q.push(current->left);
        
        if(!current->right){
            current->right = node;
            return;
        }
        else
            q.push(current->right);
    }
}

void BTree::InsertNode(int value) 
{
    // Create the new Node
    TreeNode* newNode = new TreeNode(value);
    m_count++;

    // Check if root is empty;
    if(!m_top){
        m_top = newNode;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(m_top);

    while(!q.empty())
    {
        TreeNode* current = q.front();
        q.pop();

        if(!current->left){
            current->left = newNode;
            return;
        }
        else
            q.push(current->left);
        
        if(!current->right){
            current->right = newNode;
            return;
        }
        else
            q.push(current->right);
    }
}

TreeNode* BTree::FindNode(int value)
{
    if(value == m_top->val)
        return m_top;
    std::queue<TreeNode*> q;
    q.push(m_top);

    while(!q.empty())
    {
        TreeNode* current = q.front();
        q.pop();

        if(current->val == value)
            return current;
        if(current->left)
            q.push(current->left);
        if(current->right)
            q.push(current->right);
    }

    std::cout << "Node does not exist in the tree\nReturning Nullptr\n";
    return nullptr;
}

void BTree::DeleteNode(int value)
{
    TreeNode* node = FindNode(value);
    if(!node){
        std::cout << "Node of value " << value << " not found\n";
        return;
    }

    m_count--;
    
    // Case 1: Node is a leaf node
    if(!node->left && !node->right) {
        delete node;
        node = nullptr;
        return;
    }

    // Case 2: Deleting a node with 1 child
    if(node->left || node->right) {
        if(node->left) {
            node = node->left;
            delete node->left;
            node->left = nullptr;
        }
        else {
            delete node->right;
            node = node->right;
            node->right = nullptr;
        }
        return;
    }

    // Case 3: Deleting a Node with Both children default to replacing with left
    // sift to nearest leaf node from here and replace
    if(node->left && node->right){
        std::queue<TreeNode*> q;
        q.push(node);
        TreeNode* current;
        while(!q.empty())
        {
            current = q.front();
            q.pop();
            if(current->left)
                q.push(current->left);
            if(current->right)
                q.push(current->right);
        }
        node = current;
        delete current;
        current = nullptr;
        return;
    }

}

void BST::InsertNode(int value)
{
    TreeNode* currentNode = getRoot();
    TreeNode* newNode = new TreeNode(value);

    while(true)
    {
        if(value < currentNode->val) {
            if(!currentNode->left)
                currentNode->left = newNode;
        }
    }
}

void BST::Traversal_InOrder(TreeNode* node)
{
    if(node == nullptr)
        return;
    Traversal_InOrder(node->left);
    std::cout << node->val << " ";
    Traversal_InOrder(node->right);

}

void BST::Traversal_PreOrder(TreeNode* node)
{
    if(node == nullptr)
        return;
    std::cout << node->val << " ";
    Traversal_PreOrder(node->left);
    Traversal_PreOrder(node->right);
}

void BST::Traversal_PostOrder(TreeNode* node) 
{
    if(node == nullptr)
        return;
    Traversal_PostOrder(node->left);
    Traversal_PostOrder(node->right);
    std::cout << node->val <<  " ";
}
