#ifndef TREENARY
#define TREENARY

#include "list/list.hpp"
#include "treeNary_node.hpp"

template <typename type>
class TreeNary{
private:
    // atributos
    NodeTreeNary<type> * root;

    // motodos
    void _showInPreOrder(NodeTreeNary<type> * node){
        // el arbol esta vacio
        if(node == NULL) return;
        
        // mostrar valor y hacer recursion
        else {
            std::cout << node->getValue() << " ";
        
            if(node->getDegree() == 0) return;

            for(int i = 0; i < node->getDegree(); i++)
                _showInPreOrder(node->getAtIndex(i));
        }
    }

    void _showInPostOrder(NodeTreeNary<type> * node){
        // el arbol esta vacio
        if(node == NULL) return;
        
        // mostrar valor y hacer recursion
        else {
            
            for(int i = 0; i < node->getDegree(); i++)
                _showInPostOrder(node->getAtIndex(i));
                
            std::cout << node->getValue() << " ";
        }
    }

    void _insert(NodeTreeNary<type> * node, type fatherValue, type value){
        // el arbol esta vacio
        if(node == nullptr)
        {
            // establecer el fatherValue como valor del root del arbol
            this->root = new NodeTreeNary(fatherValue);

            // recursividad para insertar en el arbol que ya no está vacio
            _insert(this->root, fatherValue, value);
        }
        
        // el arbol no esta vacio
        else
        {
            // verificar si es el nodo buscado
            if(node->getValue() == fatherValue){
                // agregar hijo a este nodo
                node->insertAtLast(new NodeTreeNary(value));
                return;
            }

            // buscar el nodo correcto
            else
            {   
                for(int i = 0; i < node->getDegree(); i++)
                    _insert(node->getAtIndex(i), fatherValue, value);
            }
        }
    }

public:
    // constructores y destructor
    TreeNary() : root(NULL) {}
    ~TreeNary(){};

    void insert(type fatherValue, type sonValue){ _insert(this->root, fatherValue, sonValue); }
    void showInPreOrder(){ _showInPreOrder(this->root); }
    void showInPostOrder(){ _showInPostOrder(this->root); }
};

#endif // TREENARY