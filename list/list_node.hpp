#pragma once

#ifndef NODELIST_HEADER
#define NODELIST_HEADER

template <typename type>
class NodeList{
private:
    type value;
    NodeList * next = NULL;
    NodeList * previous = NULL;
public:
    // constructores y destructor
    NodeList(){}
    NodeList(type value) : value(value), next(NULL), previous(NULL) {}
    ~NodeList(){};

    // setter
    void setValue(type value){this->value = value;}
    void setNext(NodeList * next){this->next = next;}
    void setPrevious(NodeList * previous){this->previous = previous;}

    // getter
    type getValue(){return this->value;}
    NodeList * getNext(){return this->next;}
    NodeList * getPrevious(){return this->previous;}
    type * getPointerToValue(){return &this->value;}
};
#endif // NODELIST_HEADER