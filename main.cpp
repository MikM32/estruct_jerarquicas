#include <iostream>
#include "BinaryTree.h"
#include "ABB.h"

using namespace std;

int main()
{
    BinTree<int> arbol1;
    ABB<int> abb;
    list<int> preorder;
    list<int> inorder;

    preorder.push_back(4);
    preorder.push_back(2);
    preorder.push_back(3);
    preorder.push_back(1);

    inorder.push_back(4);
    inorder.push_back(2);
    inorder.push_back(1);
    inorder.push_back(3);

    abb.insert(20);
    abb.insert(10);
    abb.insert(30);
    abb.insert(5);
    abb.insert(15);
    abb.insert(1);
    abb.insert(7);
    abb.insert(25);
    abb.insert(35);
    abb.insert(32);
    abb.insert(40);

    abb.deleteElem(20);

    arbol1.constructPostorder(preorder, inorder);


    list<int> preorden = abb.preorder();

    printList(preorden);

    cout << arbol1.getWeight() << endl;

    cout << "Hello world!" << endl;
    return 0;
}
