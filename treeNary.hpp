#ifndef TREENARY
#define TREENARY

#include "list/list.hpp"
#include "treeNary_node.hpp"
#include <iomanip>

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
            std::cout << setiosflags(ios::left) << setw(4) << node->getValue();
        
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
                
            std::cout << setiosflags(ios::left) << setw(4) << node->getValue();
        }
    }

    void _showInOrder(NodeTreeNary<type> * node){
        // el arbol esta vacio
        if(node == NULL) return;
        
        // mostrar valor y hacer recursion
        else {
            
            // lado izquierdo de los hijos
            for(int i = 0; i < (node->getDegree() / 2); i++)
                _showInOrder(node->getAtIndex(i));
            
            // nodo padre
            std::cout << setiosflags(ios::left) << setw(4) << node->getValue();

            // lado derecho de los hijos
            for(int i = (node->getDegree() / 2); i < node->getDegree(); i++)
                _showInOrder(node->getAtIndex(i));
        }
    }

    void _showInLevels(List<NodeTreeNary<type>*>* list, int counter){
        // el arbol esta vacio
        if(list->isEmpty()) return;

        // mostrar valor y hacer recursion
        else {

            // mostra el nivel 0
            if(counter == 0) 
                std::cout << setiosflags(ios::left) << setw(4) << list->getValueAtFirst()->getValue();

            // mostrar y agregar a la lista
            for(int i = 0; i < list->getValueAtFirst()->getDegree(); i++)
            {
                // formato de salida
                cout << setiosflags(ios::left) << setw(4);

                // (lista) -> (primer nodo) -> (Hijo i) -> (valor del hijo)
                cout << list->getValueAtFirst()->getAtIndex(i)->getValue();
                
                // agregar hijos a la lista
                list->insertAtLast(list->getValueAtFirst()->getAtIndex(i));
            }

            // eliminar elemento actual
            list->removeAtFirst();

            // llamada recursiva
            _showInLevels(list, ++counter);
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
    void showInPreOrder(){ cout << "pre-order:\t"; _showInPreOrder(this->root); cout << endl; }
    void showInPostOrder(){ cout << "post-order:\t"; _showInPostOrder(this->root); cout << endl; }
    void showInOrder(){ cout << "in-order:\t"; _showInOrder(this->root); cout << endl; }

    void showInLevels()
    {
        // lista para almacenar nodos en orden
        auto list = new List<NodeTreeNary<type>*>();

        // agregar el nodo raiz
        list->insertAtFirst(this->root);

        // mostrar mensaje de tipo de recorrido
        cout << "in-levels:\t";

        // ejecutar recorrido
        _showInLevels(list, 0);

        // mostart un salto de linea opcional
        cout << endl;
    }
};

#endif // TREENARY