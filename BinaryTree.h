#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include "NodeTree.hpp"


template <typename type>
class BinTree
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

    void postorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            this->postorder_recursive(res, curNode->getLeft());
            this->postorder_recursive(res, curNode->getRight());
            res.push_back(curNode->getValue());
        }
    }

    void inorder_recursive(list<type>& res, NodeTree<type>* curNode)
    {
        if(curNode != NULL)
        {
            this->inorder_recursive(res, curNode->getLeft());
            res.push_back(curNode->getValue());
            this->inorder_recursive(res, curNode->getRight());
        }
    }

    void constructPreorderRecur(list<type> preorderList, list<type> inorderList, NodeTree<type>* parent)
    {
        list<type> leftPartition, rightPartition;
        list<type> leftParents, rightParents;

        type rootVal = preorderList.front(), acum;

        parent->setValue(rootVal);
        this->weight++;
        preorderList.pop_front();

        acum = inorderList.front();
        inorderList.pop_front();

        while(acum != rootVal)
        {
            leftPartition.push_back(acum);
            acum = inorderList.front();
            inorderList.pop_front();

            leftParents.push_back(preorderList.front());
            preorderList.pop_front();

        }

        rightPartition = inorderList;
        rightParents = preorderList;

        if(leftPartition.size()>=1)
        {
            parent->setLeft(new NodeTree<type>());
            constructPreorderRecur(leftParents, leftPartition, parent->getLeft());
        }

        if(rightPartition.size()>=1)
        {
            parent->setRight(new NodeTree<type>());
            constructPreorderRecur(rightParents, rightPartition, parent->getRight());
        }


    }

    void constructPostorderRecur(list<type> postorderList, list<type> inorderList, NodeTree<type>* parent)
    {
        list<type> leftPartition, rightPartition;
        list<type> leftParents, rightParents;

        type rootVal = postorderList.back(), acum;

        parent->setValue(rootVal);
        this->weight++;
        postorderList.pop_back();

        acum = inorderList.back();
        inorderList.pop_back();

        while(acum != rootVal)
        {
            rightPartition.push_back(acum);
            acum = inorderList.back();
            inorderList.pop_back();

            rightParents.push_front(postorderList.back());
            postorderList.pop_back();

        }

        leftPartition = inorderList;
        leftParents = postorderList;

        if(rightPartition.size()>=1)
        {
            parent->setRight(new NodeTree<type>());
            constructPostorderRecur(rightParents, rightPartition, parent->getRight());
        }

        if(leftPartition.size()>=1)
        {
            parent->setLeft(new NodeTree<type>());
            constructPostorderRecur(leftParents, leftPartition, parent->getLeft());
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

    BinTree()
    {
        this->weight = 0;
        this->root = NULL;
    }

    BinTree(type rootVal, BinTree leftTree, BinTree rightTree)
    {
        this->weight = 0;
        this->root = NULL;
        this->create(rootVal,leftTree,rightTree);
    }
/*
    BinTree(BinTree& tree)
    {
        this->weight = tree.weight;
        this->root = tree.root;

        this->root = this->copyNode(tree.root);
    }

    BinTree(const BinTree& tree)
    {
        this->weight = tree.weight;
        this->root = tree.root;

        this->root = this->copyNode(tree.root);
    }

    ~BinTree()
    {
        if(this->root != NULL)
        {
            //this->destroy();
        }
    }*/

    void create(type rootVal, BinTree leftTree, BinTree rightTree)
    {
        //this->destroy(); // vacia el arbol antes de todo

        this->root = new NodeTree<type>(rootVal);

        this->root->setLeft(this->copyNode(leftTree.getRootNode()));

        this->root->setRight(this->copyNode(rightTree.getRootNode()));
        this->weight = 1 + rightTree.getWeight() + leftTree.getWeight();
    }

    void copy(BinTree& b)
    {
        //this->destroy();
        this->root = this->copyNode(b.root);
    }

    type getRoot()
    {
        if(this->root != NULL)
        {
            return this->root.getValue();
        }
        else
        {
            cout << "error en BinTree::getRoot(): arbol vacio."<<endl;
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

    list<type> levels()
    {
        list<type> res;

        NodeTree<type>* auxNode = NULL /*,*auxSiblings, *auxChild */;

        queue<NodeTree<type>*> auxQueue;

        if(this->root != NULL)
        {
            auxQueue.push(this->root);

            while(!auxQueue.empty())
            {
                auxNode = auxQueue.front();
                auxQueue.pop();

                res.push_back(auxNode->getValue());

                if(auxNode->getLeft() != NULL)
                {
                    auxQueue.push(auxNode->getLeft());
                }

                if(auxNode->getRight() != NULL)
                {
                    auxQueue.push(auxNode->getRight());
                }

                /*
                auxChild = auxNode->getLeft();
                auxSiblings = auxChild;

                while(auxSiblings != NULL)
                {
                    auxQueue.push(auxSiblings);
                    auxSiblings = auxSiblings->getRight();
                }*/

            }
        }

        return res;
    }

    BinTree getLeftChild()
    {
        BinTree leftChildTree;

        leftChildTree.root = leftChildTree.copyNode(this->root->getLeft());

        return leftChildTree;
    }

    BinTree getRightChild()
    {
        BinTree rightChildTree;

        rightChildTree.root = rightChildTree.copyNode(this->root->getRight());

        return rightChildTree;
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




    void constructPreorder(list<type> preorderList, list<type> inorderList)
    {
        this->root = new NodeTree<type>();
        this->constructPreorderRecur(preorderList, inorderList, this->root);
    }


    void constructPostorder(list<type> postorderList, list<type> inorderList)
    {
        this->root = new NodeTree<type>();

        this->constructPostorderRecur(postorderList, inorderList, this->root);
    }

    void destroy()
    {
        this->destroyNodes(this->root);
        this->root = NULL;
    }

    int getLevel()
    {
        int level=0;

        /*
        ============
        Por terminar
        ============
        */

        return level;
    }




};

#endif // BINARYTREE_H_INCLUDED
