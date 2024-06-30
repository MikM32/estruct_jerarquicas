#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main()
{
    BinTree<int> arbol1;
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

    arbol1.constructPostorder(preorder, inorder);


    list<int> preorden = arbol1.preorder();

    printList(preorden);

    cout << arbol1.getWeight() << endl;

    cout << "Hello world!" << endl;
    return 0;
}
