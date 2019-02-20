#include <iostream>

using namespace std;


void swap( int& a, int& b )
{
    int temp = a;
    a = b;
    b = temp;
}


void descer(int i, int array[],int n)
{
    int esq = 2*i;
    int dir = 2*i + 1;

    int maior = esq;

    if( esq <= n )
    {
        if( esq < n )
        {
            if( array[dir] > array[esq] )
			{
                maior = dir;
			}
        }

        if( array[i] < array[maior] )
        {
            swap(array[i],array[maior]);
            descer(maior,array,n);
		}
    }

}
void makeHeap(int array[],int n)
{
    for(int i = n/2 ; i>=1 ; i-- )
    {
        descer(i,array,n);
    }
}
void heapSort(int array[],int size)
{
    int temp;
    
    makeHeap(array,size);
    for(int j=1; j <= size; j++) cout << array[j] << " " ;
    cout << endl;
	cin.get();
    
    for(int i=size; i >= 2; i--)
    {
        descer(1,array,i);
	
        swap(array[i],array[1]);

        
        
        for(int j=1; j <= size; j++) cout << array[j] << " " ;
        cout << endl;
		cin.get();
        
	}



  //  }
}



int main()
{
	
	int array[] = {99, 9, 78, 43, 69, 33, 37, 12, 77, 42, 88, 15, 96, 78, 88, 17, 57, 15, 20};
	
	heapSort(array,18);
	
	cout <<"\nFinal-> ";
	for(int i=1; i <= 18; i++) cout  <<  array[i] << " " ;
	
	cin.get();
	
	
	return 0;
}
