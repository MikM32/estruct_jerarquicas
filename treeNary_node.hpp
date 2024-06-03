#ifndef TREENARY_NODE
#define TREENARY_NODE

#include "list/list.hpp"

template <typename type>
class NodeTreeNary{
private:
    type value;
    
    // children
    List<NodeTreeNary*> children = List<NodeTreeNary*>();

public:
    // constructores y destructor
    NodeTreeNary() : value(type()){}
    NodeTreeNary(type value) : value(value){}
    ~NodeTreeNary(){};

    // common
    void setValue(type value) { this->value = value; }
    type getValue() { return this->value; }
    type * getPointerToValue() { return &this->value; }

    // n-ary
    void insertAtIndex(int index, NodeTreeNary * child) { this->children.insertAtIndex(index, child); }
    void insertAtFirst(NodeTreeNary * child) { this->children.insertAtFirst(child); }
    void insertAtLast(NodeTreeNary * child) { this->children.insertAtLast(child); }

    void removeAtIndex(int index) { this->children.removeAtIndex(index); }
    void removeAtFirst() { this->children.removeAtFirst(); }
    void removeAtLast() { this->children.removeAtLast(); }
    
    NodeTreeNary * getAtIndex(int index) { return this->children.getValueAtIndex(index); }
    NodeTreeNary * getFirst() { return this->children.getValueAtFirst(); }
    NodeTreeNary * getLast() { return this->children.getValueAtLast(); }

    int getDegree() { return this->children.getSize(); }

    void modifyValueAtIndex(int index, type value) { this->children.getValueAtIndex(index)->setValue(value); }
    void modifyValueAtFirst(type value) { this->children.getValueAtFirst()->setValue(value); }
    void modifyValueAtLast(type value) { this->children.getValueAtLast()->setValue(value); }
};

#endif // TREENARY_NODE