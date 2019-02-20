#include <iostream>

using namespace std;

void troca(int &a, int &b)
{
	int temp = a;
	
	a = b;
	b = temp;
}

void quickSort(int *array,int ini, int fim)
{
	if( ini < fim )
	{
		int pivot = array[ini];
		int i = ini;
		int j = fim;
	
		while( i < j )
		{
			while( array[i] <= pivot && i < j ) i++;
			while( array[j] > pivot ) j--;
		
			if ( i < j ) troca(array[i],array[j]);
			
		}
		
		troca(array[ini],array[j]);
		
		quickSort(array,ini, j - 1 );
		quickSort(array,j + 1, fim);
	}
}

int main()
{
	int *array = NULL;
	int size;
	
	cout << "Size: "; cin >> size;
	array = new int[size];
	cout << "Insert elements " << endl;
	for(int i=0; i<size; i++) cin >> array[i];
	
	cout << "\n\nYour array before QuickSort:" << endl;
	for(int i=0; i<size; i++) cout << array[i] << " ";
	cout << endl;
	
	quickSort(array,0,size - 1);
	
	cout << "\n\nYour array after QuickSort:" << endl;
	for(int i=0; i<size; i++) cout << array[i] << " ";
	cout << endl;
	
	cin.get();
	cin.get();
	
	delete []array;
	
	return 0;
}
	
	
	
	
