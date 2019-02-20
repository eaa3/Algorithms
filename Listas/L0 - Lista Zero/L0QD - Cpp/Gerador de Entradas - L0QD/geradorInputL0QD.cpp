#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

const int MIN_N_AND_M = 5;
const int MAX_N_AND_M = 100;

const int MAX_INT_VALUE = 2147483647;

const int MAX_SIZE = 101;

unsigned long long int C[MAX_SIZE*MAX_SIZE];


int randomValue(int,int);
inline void cacheComb();


int main()
{
    cacheComb();

    srand(time(NULL));

    ofstream out("L0QD.in");

    int nEntradas = 0;
    int N,M;
    int Maior = 0;

    cout << "Quantos conjuntos de entradas? ";
    cin >> nEntradas;

    int i = 0;

    while( i < nEntradas )
    {
        N = randomValue(MIN_N_AND_M,MAX_N_AND_M);
        M = randomValue(MIN_N_AND_M,N);

        if( C[N*MAX_SIZE + M] < MAX_INT_VALUE )
        {
            out << N << " " << M << endl;

            i++;

            if( C[N*MAX_SIZE + M] > Maior )
            {
                Maior = C[N*MAX_SIZE + M];
            }


        }


    }

    cout << "A maior resposta possivel para os valores gerados foi " << Maior << endl;

    out.close();

    return 0;

}

int randomValue(int de,int ate)
{
    ate -= de;
    return rand()%(ate + 1) + de;
}

inline void cacheComb()
{
    for(int n=0; n < MAX_SIZE; n++)
    {
        for(int k=0; k <= n; k++)
        {
            if(k==0 || k==n)
            {
                C[n*MAX_SIZE + k] = 1;
            }
            else
            {
                C[n*MAX_SIZE + k] = C[(n - 1)*MAX_SIZE + (k - 1)] + C[(n - 1)*MAX_SIZE + k];
            }
        }
    }


}

