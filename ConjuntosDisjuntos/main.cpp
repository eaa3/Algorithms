#include <iostream>
#include "conjunto.h"

using namespace std;

int main()
{
    Elemento<int> elem[4];
    Conjunto<int> set;

    elem[0].dado = 10;
    elem[1].dado = 33;
    elem[2].dado = 20;
    elem[3].dado = 5;

    set.makeSet( elem );
    set.makeSet( elem + 1);
    set.makeSet( elem + 2);
    set.makeSet( elem + 3);

    set.sUnion(elem, elem+1);
    set.sUnion(elem+1, elem + 2);

    set.sUnion(elem + 3, elem);

    cout << set.findSet( elem + 3   )->dado << endl;

    return 0;
}
