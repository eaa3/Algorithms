#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int random(int de, int ate)
{
    return rand()%(ate - de + 1) + de;
}


/*
Insertion Sort parte de um array, supostamente desordenado, de tamanho N
e vai criando um novo array, ordenado, dentro deste array de tamanho N,
ao inserir ordenadamente novos elementos nesse subarray, que cresce até ficar
do tamanho do array N. Nesse ponto nosso array está totalmente ordenado
*/

template <class T>
void insertionSort(T array[], int size)
{
    int j = 0 ;
    T key;

    for(int i = 1; i<size ;i++)
    {
        key = array[i];
        j = i - 1;

        while( j >= 0 && key < array[j] ) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}


int main()
{
    srand(time(NULL));
    int *array = NULL;// = {8,2,4,9,3,6};
    int size = random(1, 30);



    //int *array = mergeSortRec(arra,0,5);

    //cout << array << endl;

    array = new int[size];
    for(int i=0; i < size; i++)
    {
        array[i] = random(0,100);
    }

    mergeSort(array,size);
    //insertionSort(array,size);

    for(int i=0;i<size;i++)
    {

        cout << array[i] << " ";
    }
   // cout << endl;

   // for(int i=0;i<100;i++) cout << random(1,10) << " " <<endl;

   // delete [] array;
}
