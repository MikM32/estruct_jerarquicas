#ifndef NODETREE_HEADER
#define NODETREE_HEADER

#include "list/list.hpp"

template <typename type>
class NodeTree{
private:
    type value;

    // binary node
    NodeTree * left = NULL;
    NodeTree * right = NULL;
    
    // n-ary node
    List<NodeTree> children = List<NodeTree>();

public:
    // constructores y destructor
    NodeTree() : value(type()), left(NULL), right(NULL) {}
    NodeTree(type value) : value(value), left(NULL), right(NULL) {}
    NodeTree(type value, NodeTree * left) : value(value), left(left), right(NULL) {}
    NodeTree(type value, NodeTree * left, NodeTree * right) : value(value), left(left), right(right) {}
    ~NodeTree(){};

    // common
    void setValue(type value) { this->value = value; }
    type getValue() { return this->value; }
    type * getPointerToValue() { return &this->value; }

    // binary
    void setLeft(NodeTree * left) { this->left = left; }
    void setRight(NodeTree * right) { this->right = right; }

    void setValueToLeft(type value) { this->left->setValue(value); }
    void setValueToRight(type value) { this->right->setValue(value); }

    NodeTree * getLeft() { return this->left; }
    NodeTree * getRight() { return this->right; }
    
    type getValueOfLeft() { return this->left->getValue(); }
    type getValueOfRight() { return this->right->getValue(); }
    
    int getDegree(){
        int result = -1;

        if(this->left == NULL && this->right == NULL){result = 0;}
        else if(this->left == NULL || this->right == NULL){result = 1;}
        if(this->left != NULL & this->right != NULL){result = 2;}

        return result;
    }

    // n-ary
    void insertChildAtIndex(int index, NodeTree child) { this->children.insertAtIndex(index, child); }
    void insertChildAtFirst(NodeTree child) { this->children.insertAtFirst(child); }
    void insertChildAtLast(NodeTree child) { this->children.insertAtLast(child); }

    void removeChildAtIndex(int index) { this->children.removeAtIndex(index); }
    void removeChildAtFirst() { this->children.removeAtFirst(); }
    void removeChildAtLast() { this->children.removeAtLast(); }
    
    NodeTree getChildAtIndex(int index) { return this->children.getValueAtIndex(index); }
    NodeTree getFirstChild() { return this->children.getValueAtFirst(); }
    NodeTree getLastChild() { return this->children.getValueAtLast(); }

    NodeTree* getPointerToChildAtIndex(int index) { return this->children.getPointerToValueAtIndex(index); }
    NodeTree* getPointerToFirstChild() { return this->children.getPointerToFirstValue(); }
    NodeTree* getPointerToLastChild() { return this->children.getPointerToLastValue(); }

    int getChildrenSize() { return this->children.getSize(); }

    void modifyValueOfChildAtIndex(int index, type value) { this->children.getPointerToValueAtIndex(index)->setValue(value); }
    void modifyValueOfChildAtFirst(type value) { this->children.getPointerToFirstValue()->setValue(value); }
    void modifyValueOfChildAtLast(type value) { this->children.getPointerToLastValue()->setValue(value); }
};

#endif // NODETREE_HEADER