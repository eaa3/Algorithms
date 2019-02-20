#include <iostream>
#include "tree.h"


using namespace std;


int main()
{
    Tree arvore;

	int n[] = {54,168,60,220,89,75,107,92,99,130,25,12,8,44};

	int k = 0;

	while(k>=0)
	{
	    cin >> k;

	    if(k>=0) arvore.add(k);
	    cout << "Caminhamento-> "; arvore.printItPreOrdem();
	}

    /*for(int i=0;i<14;i++){
		cout << "Add(" << n[i] << ")" << endl;
		arvore.add(n[i]);
		cin.get();
	}*/

   // arvore.printItPreOrdem();

    cin.get();

    return 0;
}
