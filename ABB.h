#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "BinaryTree.h"

template<typename type>

class ABB: public BinTree<type>
{
protected:


    void insertRecur(type elem, NodeTree<type>* parent)
    {

        if(elem < parent->getValue())
        {
            if(parent->getLeft() == NULL)
            {
                parent->setLeft(new NodeTree<type>(elem));
                this->weight++;
            }
            else
            {
                insertRecur(elem, parent->getLeft());

            }
        }
        else if(elem > parent->getValue())
        {
            if(parent->getRight() == NULL)
            {
                parent->setRight(new NodeTree<type>(elem));
                this->weight++;
            }
            else
            {
                insertRecur(elem, parent->getRight());
            }
        }
    }

    NodeTree<type>* findNode(type val)
    {
        NodeTree<type>* act = this->root;

        while(act != NULL)
        {
            if(act->getValue() == val)
            {
                return act;
            }
            else if(val < act->getValue())
            {

                act = act->getLeft();

            }
            else
            {
                act = act->getRight();
            }
        }

        return act; // retorna NULL

    }



    NodeTree<type>* findMinNode(NodeTree<type>* parent)
    {
        queue<NodeTree<type>*> auxQueue;
        NodeTree<type>* res = parent, *act = parent;

        auxQueue.push(parent);

        while(!auxQueue.empty())
        {
            act = auxQueue.front();
            auxQueue.pop();

            if(act->getValue() < res->getValue())
            {
                res = act;
            }

            if(act->getLeft() != NULL)
            {
                auxQueue.push(act->getLeft());
            }

            if(act->getRight() != NULL)
            {
                auxQueue.push(act->getRight());
            }
        }

        return res;
    }

    void deleteElemRecursive(type elem, NodeTree<type>* parent)
    {
        NodeTree<type>* delNode = NULL, *act = parent, *aux = NULL;
        NodeTree<type>* delNodeParent = NULL;

        while(act != NULL) // Busqueda del nodo y del padre del nodo
        {
            if(act->getValue() == elem)
            {
                delNode = act;
                break;
            }
            else if(elem < act->getValue())
            {
                delNodeParent = act;
                act = act->getLeft();

            }
            else
            {
                delNodeParent = act;
                act = act->getRight();
            }
        }

        if(delNode)
        {
            if((delNode->getRight() != NULL && delNode->getLeft() != NULL) || !delNodeParent) // Tiene ambos hijos o es el nodo raiz
            {
                aux = findMinNode(delNode->getRight());

                delNode->setValue(aux->getValue());

                deleteElemRecursive(aux->getValue(), delNode->getRight());
            }
            else if(delNode->getRight() != NULL) // Si hay un nodo a la derecha pero no a la izquierda
            {

                if(delNodeParent->getValue() > delNode->getValue())
                {
                    delNodeParent->setLeft(delNode->getRight());
                }
                else // Se hace asi porque se entiende que no hay elementos repetidos
                {
                    delNodeParent->setRight(delNode->getRight());
                }

                delete delNode;
            }
            else if(delNode->getLeft() != NULL) // Si hay un nodo a la izquierda pero no a la derecha
            {
                if(delNodeParent->getValue() > delNode->getValue()) // verifica si es un hijo izquierdo o derecho
                {
                    delNodeParent->setLeft(delNode->getLeft());
                }
                else // Se hace asi porque se entiende que no hay elementos repetidos
                {
                    delNodeParent->setRight(delNode->getLeft());
                }

                delete delNode;
            }
            else // Es hoja
            {
                if(delNodeParent->getValue() > delNode->getValue())
                {
                    delNodeParent->setLeft(NULL);
                }
                else // Se hace asi porque se entiende que no hay elementos repetidos
                {
                    delNodeParent->setRight(NULL);
                }
                delete delNode;
            }
        }
    }

public:


    ABB()
    {
        this->root = NULL;
        this->weight = 0;
    }

    void insert(type elem)
    {

        if(this->isEmpty())
        {
            this->root = new NodeTree<type>(elem);
            this->weight++;
        }
        else if(!this->find(elem)) // Si no encuentra al elemento en el arbol entonces inserta
        {
            insertRecur(elem, this->root);
        }


    }

    bool find(type elem)
    {
        if(this->isEmpty())
        {
            return false;
        }
        else
        {
            return findNode(elem) != NULL;
        }
    }


    void deleteElem(type elem)
    {
        this->deleteElemRecursive(elem, this->root);
    }


};

#endif // ABB_H_INCLUDED
