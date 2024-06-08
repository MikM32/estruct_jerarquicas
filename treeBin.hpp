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
    void _showInPreorder(NodeTreeBin<type> * node){
        // el arbol esta vacio
        if(node == NULL) return;
        
        // mostrar valor y hacer recursion
        else {
            std::cout << node->getValue() << " ";
        
            if(node->getDegree() == 0) return;

            _showInPreorder(node->getLeft());
            _showInPreorder(node->getRight());
        }
    }

    void _insertOld(NodeTreeBin<type> * node, type value){
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

    void _insertInPreOrder(NodeTreeBin<type> *& node, List<type> * inorder, List<type> * preorder){
        // caso base
        if(inorder->getSize() == 0 || preorder->getSize() == 0) return;

        // insertar nodo actual
        node = new NodeTreeBin(preorder->getValueAtFirst());

        // hijos izquierdo y derecho
        List<type> * left_inorder = new List<type>();
        List<type> * left_preorder = new List<type>();
        List<type> * right_inorder = new List<type>();
        List<type> * right_preorder = new List<type>();

        // llenar listas inorder
        for(int i = 0; (i < inorder->getSize()) && (inorder->getValueAtIndex(i) != preorder->getValueAtFirst()); i++)
            left_inorder->insertAtLast(inorder->getValueAtIndex(i));

        for(int i = inorder->getIndexOfValue(preorder->getValueAtFirst()) + 1; i < inorder->getSize(); i++)
            right_inorder->insertAtLast(inorder->getValueAtIndex(i));

        // llenar listas preorder
        for(int i = 1; i < left_inorder->getSize() + 1; i++)
            left_preorder->insertAtLast(preorder->getValueAtIndex(i));

        for(int i = (left_preorder->getSize() + 1); i < preorder->getSize(); i++)
            right_preorder->insertAtLast(preorder->getValueAtIndex(i));

        // llamada recursiva
        _insertInPreOrder(*node->getPointerToLeft(), left_inorder, left_preorder);
        _insertInPreOrder(*node->getPointerToRight(), right_inorder, right_preorder);

        // liberar memoria dinamica
        left_inorder->clear();
        left_preorder->clear();
        right_inorder->clear();
        right_preorder->clear();
    }

public:
    // constructores y destructor
    TreeBin() : root(NULL) {}
    ~TreeBin(){};

    void showInPreorder(){ _showInPreorder(this->root); }

    void insertInPreOrder(List<type> * inorder, List<type> * preorder){
        _insertInPreOrder(this->root, inorder, preorder);
    }
};

#endif // TREEBINARY