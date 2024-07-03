#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include "NodeTree.hpp"


template <typename type>
class BinTree
{
protected:
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
	
	void findNode(NodeTree<type>* parent, NodeTree<type>*& node_salida, type elem)
	{
		if(parent != NULL)
		{
			if(parent->getValue() == elem)
			{
				node_salida = parent;
			}
			else
			{
				findNode(parent->getLeft(), node_salida, elem);
				findNode(parent->getRight(), node_salida, elem);
			}
		}
	}
	
	void findParentNode(NodeTree<type>* parent, NodeTree<type>*& parent_salida, type elem)
	{
		if(parent != NULL)
		{
			
			if(parent->getRight() != NULL)
			{
				if(parent->getRight()->getValue() == elem)
				{
					parent_salida = parent;
				}
			}
			if(parent->getLeft() != NULL)
			{
				if(parent->getLeft()->getValue() == elem)
				{
					parent_salida = parent;
				}
				
			}
			
			findParentNode(parent->getLeft(), parent_salida, elem);
			findParentNode(parent->getRight(), parent_salida, elem);
		}
	}
	
	bool getPathRecur(list<type>& path, NodeTree<type>* parent, type elem)
	{
		if(parent == NULL)
		{
			return false;
		}
		
		path.push_back(parent->getValue());
		
		if(parent->getValue() == elem)
		{
			return true;
		}
		
		if(getPathRecur(path, parent->getLeft(), elem) || getPathRecur(path, parent->getRight(), elem))
		{
			return true;
		}
		
		
		path.pop_back();
		return false;
			
	}
	
    bool isEqualNode(NodeTree<type>* parent1, NodeTree<type>* parent2) // Metodo recursivo del metodo isEqual
    {
        bool band = false;

        if(parent1 == NULL && parent2 == NULL)
        {
            return true;
        }

        if((parent1 != NULL && parent2 != NULL))
        {

            if(parent1->getValue() == parent2->getValue())
            {
                band = isEqualNode(parent1->getLeft(), parent2->getLeft());
                band = band && isEqualNode(parent1->getRight(), parent2->getRight());
            }
            else
            {
                return false;
            }
        }

        return band;
    }

    bool isIsomorphicNode(NodeTree<type>* parent1, NodeTree<type>* parent2) //metodo recursivo para isIsomorphic
    {
        bool band = false;

        if(parent1 == NULL && parent2 == NULL)
        {
            return true;
        }

        if((parent1 != NULL && parent2 != NULL))
        {

            band = true;
            band = band && isIsomorphicNode(parent1->getLeft(), parent2->getLeft());
            band = band && isIsomorphicNode(parent1->getRight(), parent2->getRight());
        }

        return band;
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

    int getWeight() //getPeso
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

	
	
    BinTree getLeftChild() // getHijoIzq
    {
        BinTree leftChildTree;

        leftChildTree.root = leftChildTree.copyNode(this->root->getLeft());

        return leftChildTree;
    }

    BinTree getRightChild() // getHijoDer
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

    bool isEqual(BinTree<type> tree) //esIgual
    {
        if(this->isEmpty() && tree.isEmpty())
        {
            return true;
        }
        else if((this->isEmpty() && !tree.isEmpty()) || (!this->isEmpty() && tree.isEmpty()))
        {
            return false;
        }
        else
        {
            return isEqualNode(this->root, tree.root);
        }
    }

    bool isIsomorphic(BinTree<type> tree) // esIsomorfo
    {
        if(this->isEmpty() && tree.isEmpty())
        {
            return true;
        }
        else if((this->isEmpty() && !tree.isEmpty()) || (!this->isEmpty() && tree.isEmpty()))
        {
            return false;
        }
        else
        {
            return isIsomorphicNode(this->root, tree.root);
        }
    }
	
	void lca(NodeTree<type>* ptr, const type &e1, const type &e2, bool&found1, bool& found2, bool &lcafound, NodeTree<type>*& ancestor)
	{
		bool foundE1Left, foundE2Left, foundE1Right, foundE2Right;
		
		if(!lcafound && ptr != NULL)
		{
			if(ptr->isLeaf())
			{
				found1 = ptr->getValue() == e1;
				
				found2 = ptr->getValue() == e2;
				
			}
			else
			{
				foundE1Left = false;
				foundE2Left = false;
				foundE1Right = false;
				foundE2Right = false;
				
				lca(ptr->getLeft(), e1, e2, foundE1Left, foundE2Left, lcafound, ancestor);
				lca(ptr->getRight(), e1, e2, foundE1Right, foundE2Right, lcafound, ancestor);
				
				if(!lcafound)
				{
					found1 = foundE1Left || foundE2Left || ptr->getValue() == e1;
					found2 = foundE1Right || foundE2Right || ptr->getValue() == e2;
					
					lcafound = found1 && found2;
					
					if(lcafound)
					{
						ancestor = ptr;
					}
				}
			}
			
			
		}
	}
	
	type lca(const type& elem1, const type& elem2) // Lower Common Ancestor / Ancestro Comun mas Bajo
	{
		NodeTree<type>* ancestor = NULL;
		bool found1 = false, found2 = false, lcafound=false;
		
		lca(this->root, elem1, elem2, found1,found2, lcafound, ancestor);
		
		if(ancestor != NULL)
		{
			return ancestor->getValue();
			
		}
		
		return type();
	}
	
	list<type> getPath(type elem)
	{
		list<type> path;
		
		this->getPathRecur(path, this->root, elem);
		
		return path;
	}
	
	list<type> getPathBetween(type elem1, type elem2)
	{
		list<type> path_res, path1l, path2l;
		
		
		path1l = getPath(elem1);
		path2l = getPath(elem2);
		
		//Transforma list<type> a vector<type>
		vector<type> path1(path1l.begin(), path1l.end());
		vector<type> path2(path2l.begin(), path2l.end());
		
		int intersection = -1;
		int i =0, j=0;
		
		while(i!= (int)path1.size() || j != (int)path2.size())
		{
			if(i==j && path1[i] == path2[j])
			{
				i++;
				j++;
			}
			else
			{
				intersection = j-1; // Le resta uno para omitir un elemento que se repite en ambos caminos
									// (para que no se repita dos veces)
				break;
			}
		}
		
		for(int i = path1.size()-1; i> intersection; i--)
		{
			path_res.push_back(path1[i]);
		} 
		
		for(int i = intersection; i < path2.size(); i++)
		{
			path_res.push_back(path2[i]);
		}
		
		return path_res;
	}

    void deleteSubTree(BinTree<type> sub)
    {
		
        NodeTree<type>* auxNode = NULL;

        queue<NodeTree<type>*> auxQueue;

        if(this->root != NULL)
        {
            auxQueue.push(this->root);

            while(!auxQueue.empty())
            {
                auxNode = auxQueue.front();
                auxQueue.pop();

                

                if(auxNode->getLeft() != NULL)
                {
					if(auxNode->getLeft() == sub.root->getValue())
					{
						this->destroyNodes(auxNode->getLeft());
						auxNode->setLeft(NULL);
						break;
					}
                    auxQueue.push(auxNode->getLeft());
                }

                if(auxNode->getRight() != NULL)
                {
					if(auxNode->getRight() == sub.root->getValue())
					{
						this->destroyNodes(auxNode->getRight());
						auxNode->setRight(NULL);
						break;
					}
                    auxQueue.push(auxNode->getRight());
                }

	
            }
        }
    }
	
	type getParent(type elem) // getPadre
	{
		NodeTree<type>* parent = findParentNode(this->root, elem);
		
		if(parent != NULL)
		{
			return parent->getValue();
		}
	}
	
	
	list<type> getCousins(type elem1) //getPrimos
	{
		NodeTree<type>* elemNode = NULL, *uncle; // Nodo tio
		NodeTree<type>* parentNode = NULL; //Nodo padre
		NodeTree<type>* grandParentNode = NULL; //Nodo abuelo
		
		findNode(this->root, elemNode, elem1);
		findParentNode(this->root, parentNode, elem1);
		
		if(parentNode != NULL) // Si el elemento actual tiene padre entonces busca a su abuelo
		{
			findParentNode(this->root, grandParentNode, parentNode->getValue());	
		}
		
		
		list<type> cousins;
		
		if(elemNode != NULL && grandParentNode != NULL) // si se encontro al elemento y tiene abuelo
		{
			uncle = grandParentNode->getLeft();
			if(uncle != NULL && uncle->getValue() != parentNode->getValue()) // Se verifica si el elemento de la izquierda es un tio y no su padre
			{
				if(uncle->getLeft() != NULL)
				{
					cousins.push_back(uncle->getLeft()->getValue());
				}
				
				if(uncle->getRight() != NULL)
				{
					cousins.push_back(uncle->getRight()->getValue());
				}
			}
			
			uncle = grandParentNode->getRight();
			if(uncle != NULL && uncle->getValue() != parentNode->getValue())
			{
				if(uncle->getLeft() != NULL)
				{
					cousins.push_back(uncle->getLeft()->getValue());
				}
				
				if(uncle->getRight() != NULL)
				{
					cousins.push_back(uncle->getRight()->getValue());
				}
			}
		}
		
		return cousins;
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


    bool isLeaf()
    {
        return (this->root->getLeft() == NULL) && (this->root->getRight() == NULL);
    }

};

#endif // BINARYTREE_H_INCLUDED
