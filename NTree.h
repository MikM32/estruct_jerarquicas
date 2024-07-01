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
            this->preorder_recursive(res, curNode->getRight());
        }
    }

    void postorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            this->postorder_recursive(res, curNode->getLeft());

            //NodeTree<type>* acum = curNode->getRight();
            res.push_back(curNode->getValue()); // Se que este es el inorden pero solo asi me devuelve el recorrido en postorden Xd
            this->postorder_recursive(res, curNode->getRight());
            /*while(acum!=NULL)
            {

                this->postorder_recursive(res, acum);
                acum = acum->getRight();
            }*/

        }
    }

    void inorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            this->inorder_recursive(res, curNode->getLeft());

            res.push_back(curNode->getValue());

            if(curNode->getLeft() != NULL)
            {
                NodeTree<type>* acum = curNode->getLeft()->getRight();

                while(acum != NULL)
                {
                    inorder_recursive(res, acum);
                    acum = acum->getRight();
                }
            }

        }
    }

    NodeTree<type>* copyNode(NodeTree<type>* node)
    {
        NodeTree<type>* newNode = NULL;

        if(node != NULL)
        {
            this->weight++;
            newNode = new NodeTree<type>(node->getValue(), this->copyNode(node->getLeft()),  this->copyNode(node->getRight()));
        }

        return newNode;
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

    void insertNode(type parent, type elem, NodeTree<type>* parentNode)
    {
        NodeTree<type>* newNode = NULL, *aux = NULL;

        if(parentNode != NULL)
        {
            if(parentNode->getValue() == parent)
            {
                if(parentNode->getLeft()== NULL)
                {
                    newNode = new NodeTree<type>(elem);
                    parentNode->setLeft(newNode);
                }
                else
                {
                    newNode = new NodeTree<type>(elem);
                    aux = parentNode->getLeft();
                    while(aux->getRight() != NULL)
                    {
                        aux = aux->getRight();
                    }

                    aux->setRight(newNode);
                }
            }
            else
            {
                insertNode(parent, elem, parentNode->getLeft());
                insertNode(parent, elem, parentNode->getRight());
            }
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

    Ntree(type root, list<Ntree<type>> childs)
    {
        this->root = new NodeTree<type>(root);

        if(!childs.empty())
        {
            this->root->setLeft(this->copyNode(childs.front().root));
            childs.pop_front();

            NodeTree<type>* acum = this->root->getLeft();
            while(!childs.empty())
            {
                acum->setRight(this->copyNode(childs.front().root));
                childs.pop_front();
                acum = acum->getRight();
            }
        }
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

    void insert(type parent, type elem)
    {
        this->insertNode(parent, elem, this->root);
    }



    void insertSubTree(Ntree<type> sub)
    {
        if(this->root->getLeft() == NULL)
        {
            this->root->setLeft(this->copyNode(sub.root));
        }
        else
        {
            NodeTree<type>* acum = this->root->getLeft();
            while(acum->getRight() != NULL)
            {
                acum = acum->getRight();
            }

            acum->setRight(this->copyNode(sub.root));
        }
    }

    list<type> preorder()
    {
        list<type> res;
        this->preorder_recursive(res, this->root);

        return res;
    }

    list<type> postorder()
    {
        list<type> res;
        this->postorder_recursive(res, this->root);

        return res;
    }

    list<type> inorder()
    {
        list<type> res;
        this->inorder_recursive(res, this->root);

        return res;
    }



};

#endif // NTREE_H_INCLUDED
