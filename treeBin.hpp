#ifndef TREEBINARY
#define TREEBINARY

#include "list/list.hpp"
#include "treeBin_node.hpp"

template <typename type>
class TreeBin{
private:
    // atributos
    NodeTreeBin<type> * root;

    // motodos
    void _show(NodeTreeBin<type> * node){
        // el arbol esta vacio
        if(node == NULL) return;
        
        // mostrar valor y hacer recursion
        else {
            std::cout << node->getValue() << " ";
        
            if(node->getDegree() == 0) return;

            _show(node->getLeft());
            _show(node->getRight());
        }
    }

    void _insert(NodeTreeBin<type> * node, type value){
        // el arbol esta vacio
        if(node == NULL){
            this->root = new NodeTreeBin(value); 
        }

        // no tiene hijos
        else if(node->getDegree() == 0){
            node->setLeft(new NodeTreeBin(value));
        }

        // tiene un solo hijo
        else if(node->getDegree() == 1){
            cout << "grado: " << node->getDegree() << endl;
            if(node->getLeft() == NULL)
                node->setLeft(new NodeTreeBin(value));
            else
                node->setRight(new NodeTreeBin(value));
        }

        // tiene dos hijos (toca recursion)
        else if(node->getDegree() == 2){
            if(node->getLeft()->getDegree() < 2)
                _insert(node->getLeft(), value);
            else
                _insert(node->getRight(), value);
        }
    }

public:
    // constructores y destructor
    TreeBin() : root(NULL) {}
    ~TreeBin(){};

    void insert(type value){ _insert(this->root, value); }
    void show(){ _show(this->root); }
};

#endif // TREEBINARY