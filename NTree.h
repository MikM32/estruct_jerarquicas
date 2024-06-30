#ifndef NTREE_H_INCLUDED
#define NTREE_H_INCLUDED

#include "NodeTree.hpp"

template <typename type>
class Ntree // Izquierda para hijos y derecha para hermanos
{
private:

    int weight;
    NodeTree<type>* root;

    void preorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            res.push_back(curNode->getValue());
            this->preorder_recursive(res, curNode->getLeft());
            this->preorder_recursive(res, curNode->getRight());
        }
    }

public:

    Ntree()
    {
        this->weight = 0;
        this->root = NULL;
    }

    type getRoot()
    {
        if(this->root != NULL)
        {
            return this->root.getValue();
        }
        else
        {
            cout << "error en ArbolN::getRoot(): arbol vacio."<<endl;
            return type();
        }
    }

    bool isEmpty()
    {
        return this->root == NULL || this->weight == 0;
    }

    int getWeight()
    {
        return this->weight;
    }

    list<type> preorder()
    {
        list<type> res;
        this->preorder_recursive(res, this->root);

        return res;
    }

    void insertByLevel(type elem) // Insercion por niveles (BFS)
    {
        NodeTree<type>* newNode = new NodeTree<type>(elem);
        NodeTree<type>* auxNode = NULL, *auxLeft, *auxRight;

        queue<NodeTree<type>*> auxQueue;

        if(this->root == NULL)
        {
            this->root = newNode;

        }else
        {
            auxQueue.push(this->root);

            while(!auxQueue.empty())
            {
                auxNode = auxQueue.front();
                auxQueue.pop();

                auxLeft = auxNode->getLeft();
                auxRight = auxNode->getRight();



                if(auxLeft == NULL)// Si el hijo izquierdo es nulo se inserta alli
                {
                    auxNode->setLeft(newNode);

                    break;
                }
                else
                {
                    auxQueue.push(auxLeft);
                }

                if(auxRight == NULL) // Si el hijo derecho es nulo se inserta alli
                {
                    auxNode->setRight(newNode);
                    break;
                }
                else
                {
                    auxQueue.push(auxRight);
                }


            }
        }

        this->weight++;
    }

};

#endif // NTREE_H_INCLUDED
