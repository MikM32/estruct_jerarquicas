#ifndef TREEBINARY_NODE
#define TREEBINARY_NODE

template <typename type>
class NodeTreeBin{
private:
    type value;

    // binary node
    NodeTreeBin * left = nullptr;
    NodeTreeBin * right = nullptr;

public:
    // constructores y destructor
    NodeTreeBin() : value(type()), left(nullptr), right(nullptr) {}
    NodeTreeBin(type value) : value(value), left(nullptr), right(nullptr) {}
    NodeTreeBin(type value, NodeTreeBin * left) : value(value), left(left), right(nullptr) {}
    NodeTreeBin(type value, NodeTreeBin * left, NodeTreeBin * right) : value(value), left(left), right(right) {}
    ~NodeTreeBin(){};

    // common
    void setValue(type value) { this->value = value; }
    type getValue() { return this->value; }
    type * getPointerToValue() { return &this->value; }

    // binary
    void setLeft(NodeTreeBin * left) { this->left = left; }
    void setRight(NodeTreeBin * right) { this->right = right; }

    void setValueToLeft(type value) { this->left->setValue(value); }
    void setValueToRight(type value) { this->right->setValue(value); }

    NodeTreeBin * getLeft() { return this->left; }
    NodeTreeBin * getRight() { return this->right; }

    NodeTreeBin ** getPointerToLeft() { return &this->left; }
    NodeTreeBin ** getPointerToRight() { return &this->right; }
    
    type getValueOfLeft() { return this->left->getValue(); }
    type getValueOfRight() { return this->right->getValue(); }
    
    int getDegree(){
        int result = -1;

        if(this->left == nullptr && this->right == nullptr){result = 0;}
        else if(this->left == nullptr || this->right == nullptr){result = 1;}
        if(this->left != nullptr && this->right != nullptr){result = 2;}

        return result;
    }
};

#endif // TREEBINARY_NODE