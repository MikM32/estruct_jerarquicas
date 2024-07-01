#ifndef NTREE_H_INCLUDED
#define NTREE_H_INCLUDED

#include "NodeTree.hpp"

template <typename type>
class Ntree // Izquierda para hijos y derecha para hermanos
{
private:

    int weight;
    NodeTree<type>* root, *acum;

    void preorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            res.push_back(curNode->getValue());
            this->preorder_recursive(res, curNode->getLeft());

            acum = curNode->getRight();

            while(acum != NULL)
            {
                this->preorder_recursive(res, acum);
                acum = acum->getRight();
            }

        }
    }

    NodeTree<type>* copyNode(NodeTree<type>* node)
    {
        NodeTree<type>* newNode;

        if(node != NULL)
        {
            this->weight++;
            newNode = new NodeTree<type>(node->getValue(), this->copyNode(node->getLeft()),  this->copyNode(node->getRight()));
            return newNode;
        }

        return NULL;
    }

    void destroyNodes(NodeTree<type>* node)
    {
        if(node != NULL)
        {
            if(node->getRight() != NULL)
            {
                destroyNodes(node->getRight());
            }

            if(node->getLeft() != NULL)
            {
                destroyNodes(node->getLeft());
            }

            delete node;
            this->weight--;
        }
    }

    NodeTree<type>* getRootNode()
    {
        return this->root;
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



};

#endif // NTREE_H_INCLUDED
