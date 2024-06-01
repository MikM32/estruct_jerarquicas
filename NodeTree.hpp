#pragma once

#ifndef NODE_HEADER
#define NODE_HEADER

#include "list/list.hpp"

template <typename type>
class NodeTree{
private:
    type value;

    // binary node
    Node * left = NULL;
    Node * right = NULL;
    
    // n-ary node
    List<NodeTree> children = List<NodeTree>();

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
