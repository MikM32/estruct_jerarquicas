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
    Node() : value(type()), left(NULL), right(NULL) {}
    Node(type value) : value(value), left(NULL), right(NULL) {}
    Node(type value, Node * left) : value(value), left(left), right(NULL) {}
    Node(type value, Node * left, Node * right) : value(value), left(left), right(right) {}
    ~Node(){};

    // setter
    void setValue(type value){this->value = value;}
    void setRight(Node * right){this->right = right;}
    void setLeft(Node * left){this->left = left;}

    // getter
    type getValue(){return this->value;}
    type getValueOfLeft(){return this->left->getValue();}
    type getValueOfRight(){return this->right->getValue();}

    Node * getRight(){return this->right;}
    Node * getLeft(){return this->left;}
    type * getPointerToValue(){return &this->value;}
};

#endif // NODE_HEADER