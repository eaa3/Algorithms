#include <iostream>
#include "heap.h"

using namespace std;

void print(Heap &heap)
{
    for(int i=1; i<=heap.n ; i++ ) cout << heap.array[i] << " ";
    cout << endl;
}

int main()
{
    Heap heap(10);
    int in;
    cout << "Insercao"<<endl;
    while(heap.n < heap.getSize())
    {
        cin >> in;
        heap.inserir(in);
        print(heap);
        cout << endl;
    }
    cout << "Remoção"<<endl;
    int cont = 1;
    cin.get();
    while( heap.n> 0 )
    {
        cout << cont << "->TesteRemover = " << heap.remover(&in) << endl;
        cout << "Removido= " << in << endl;
        print(heap);
        cout << endl;

        cin.get();
        cont++;

    }

    cout << "TesteK = " << heap.remover(&in) << endl;
    cout << "Removido= " << in << endl;
    cout << "TesteX = " << heap.remover(&in) << endl;
    cout << "Removido= " << in << endl;
    cout << "TesteY = " << heap.remover(&in) << endl;
    cout << "Removido= " << in << endl;


    cin.get();

    return 0;
}
