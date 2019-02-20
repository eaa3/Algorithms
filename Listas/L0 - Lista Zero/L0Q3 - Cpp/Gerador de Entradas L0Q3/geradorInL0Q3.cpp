#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdlib>

using std::endl;
using std::cout;
using std::cin;
using std::ofstream;

const int MIN_L_AND_M = 1;
const int MAX_L_AND_M = 100;

const int MIN_ELEMENT_VALUE = 0;
const int MAX_ELEMENT_VALUE = 1000;




int randomValue(int,int);

int main()
{
    srand(time(NULL));

    ofstream out("L0Q3.in");

    int nEntradas,L,M;

    L = M = nEntradas = 0;

    cout << "Quantos conjuntos devem ser gerados? ";
    cin >> nEntradas;

    for(int n=0; n < (nEntradas*2) ; n++)
    {
        if(n%2==0 && n>0) out << endl;
        cout << "Insira MxN." << endl;
        cin >> L >> M;
        
        if( !L || !M ) {
            L = randomValue(MIN_L_AND_M,MAX_L_AND_M);
            M = randomValue(MIN_L_AND_M,MAX_L_AND_M);
        }

        out << L << " " << M << endl;

        for(int i = 0; i < L ; i++)
        {
            for(int j = 0; j < M ; j++)
            {

                out << randomValue(MIN_ELEMENT_VALUE,MAX_ELEMENT_VALUE) << " ";
            }

            out << endl;

        }



    }

    return 0;
}

int randomValue(int de,int ate)
{
    ate -= de;
    return rand()%ate + de;
}
