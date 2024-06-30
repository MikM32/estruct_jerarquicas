#ifndef NODE_HEADER
#define NODE_HEADER

#include <list>
#include <queue>
#include <stack>
#include <algorithm>

#include "utils.h"

using namespace std;

template <typename type>
class NodeTree{
private:
    type value;

    // binary node
    NodeTree<type>* left = NULL;   // para N-arios seria hijo_izquierdo
    NodeTree<type>* right = NULL; // para N-arios seria hermano_derecho



public:
    // constructores y destructor
    NodeTree() : value(type()), left(NULL), right(NULL) {}
    NodeTree(type value) : value(value), left(NULL), right(NULL) {}
    NodeTree(type value, NodeTree<type>* left) : value(value), left(left), right(NULL) {}
    NodeTree(type value, NodeTree<type>* left, NodeTree<type>* right) : value(value), left(left), right(right) {}
    ~NodeTree(){};

    // setter
    void setValue(type value){this->value = value;}
    void setRight(NodeTree<type>* right){this->right = right;}
    void setLeft(NodeTree<type>* left){this->left = left;}


    // getter
    type getValue(){return this->value;}
    NodeTree<type>* getRight(){return this->right;}
    NodeTree<type>* getLeft(){return this->left;}



    type * getPointerToValue(){return &this->value;}
};

#endif // NODE_HEADER
