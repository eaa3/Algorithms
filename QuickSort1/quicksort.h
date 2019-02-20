#ifndef _QUICKSORT_
#define _QUICKSORT_

#include <iostream>


using namespace std;

template <class T>
void troca(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void quickSort(T array[],int begin, int end)
{
    if( begin < end)
    {
        int pivot = array[begin];
        int i,j;

        i = begin + 1;
        j = end;



        //cout << "i= " << i << " j= " << j << " Pivot= " << pivot<< endl;

        while( i < j )
        {
            while( array[i] < pivot && i<end ) i++;
            while( array[j] > pivot) j--;

            if( i < j) troca<T>( array[i], array[j]);


            for(int k=begin; k < end; k++) cout << array[k] << " ";

            cout << "\ni= " << i << " j= " << j << " Pivot= " << pivot<< endl;

            cin.get();

        }

        troca(array[j],array[begin]);


        quickSort(array,begin, j - 1);
        quickSort(array,j+1, end);
    }




}

#endif
