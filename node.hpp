#pragma once

#ifndef NODE_HEADER
#define NODE_HEADER

template <typename type>
class Node{
private:
    type value;
    Node * left = NULL;
    Node * right = NULL;
public:
    // constructores y destructor
    Node(){}
    Node(type value) : value(value), right(NULL), left(NULL) {}
    ~Node(){};

    // setter
    void setValue(type value){this->value = value;}
    void setRight(Node * right){this->right = right;}
    void setLeft(Node * left){this->left = left;}

    // getter
    type getValue(){return this->value;}
    Node * getRight(){return this->right;}
    Node * getLeft(){return this->left;}
    type * getPointerToValue(){return &this->value;}
};

#endif // NODE_HEADER