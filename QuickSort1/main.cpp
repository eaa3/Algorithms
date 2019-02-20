#include "quicksort.h"




int main()
{
    int ar[] = { 1 , 10, 50, 20, 45};

    int begin = 0;
    int end = 4;

    quickSort(ar,begin,end);


    for(int i=0;i<=end;i++) cout << ar[i] << " ";


    return 0;

}
