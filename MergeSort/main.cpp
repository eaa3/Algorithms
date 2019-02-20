#include <iostream>
#include <time.h>
#include <stdlib.h>


using namespace std;

int random(int de, int ate)
{
    return rand()%(ate - de + 1) + de;
}


template <class T>
T* merge(T arrayA[],T arrayB[], int endA, int endB)
{
    //Merged array
    T *mArray = new T[endA + endB];

    int i = 0;
    int j = 0;
    int k = 0;

    while ( i<endA && j<endB )
    {
        if( arrayA[i] <= arrayB[j] )
        {
            mArray[k] = arrayA[i];
            i++;
            k++;
        }
        else
        {
            mArray[k] = arrayB[j];
            j++;
            k++;
        }
    }

    while( i< endA ){
        mArray[k] = arrayA[i];
        k++;
        i++;
    }
    while( j< endB ) {
        mArray[k] = arrayB[j];
        k++;
        j++;
    }

    return mArray;

}
//begin = primeiro índice válido
//end = último índice válido
template <class T>
T* mergeSortRec(T array[],int begin, int end)
{
    if( (end - begin ) <= 0 )
    {
        T* temp = new T[1];
        temp[0] = array[begin];

        return temp;
    }
    else
    {

        T* retorno = NULL;

        T* arrayA = mergeSortRec(array, begin, (begin+end)/2);
        T* arrayB = mergeSortRec(array, (begin+end)/2 + 1, end );


        retorno = merge(arrayA,arrayB,(end - begin)/2 + 1 , (end - begin + 1)/2 );

        delete [] arrayA;
        delete [] arrayB;

        return retorno;

    }

}


template <class T>
void mergeSort(T array[], int size)
{
    T* temp = mergeSortRec(array,0,size - 1);

    for(int i=0;i<size;i++) array[i] = temp[i];

    delete []temp;
}

int main()
{
    srand(time(NULL));
    int *array = NULL;// = {8,2,4,9,3,6};
    int size = random(1, 10);



    //int *array = mergeSortRec(arra,0,5);


    array = new int[size];
    cout << "Sequencia gerada" << endl;
   // int array[] = { 21, 95, 1 ,56};
   // size = 4;
    for(int i=0; i < size; i++)
    {
        array[i] = random(0,100);
        cout << array[i] << " ";
    }

    cout << endl;
    cout << "\nSequencia ordenada " << endl;
    mergeSort(array,size);
    cout << "Size= " << size << endl;
    for(int i=0;i<size;i++)
    {

        cout << array[i] << " ";
    }
    cout << endl;

   // for(int i=0;i<100;i++) cout << random(1,10) << " " <<endl;

    delete [] array;
}

