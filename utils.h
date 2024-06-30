#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>

using namespace std;

template <typename type>
void printList(list<type> lista)
{
    for(auto &a: lista)
    {
        if(a)
        {
            cout << a << " ";
        }
    }

    cout << endl;
}

#endif // UTILS_H_INCLUDED
