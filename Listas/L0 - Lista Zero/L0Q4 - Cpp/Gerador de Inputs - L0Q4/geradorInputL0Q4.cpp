#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int MAX_NM = 200;

int random(int de,int ate)
{
    return rand()%(ate - de + 1) + de;
}

int main()
{

    srand(time(NULL));

    ofstream out("L0Q4.in");

    int nEntradas = 0;
    int M,N;

    cout << "Gerar quantos conjuntos de entrada?";
    cin >> nEntradas;

    for(int i = 0; i < nEntradas ; i++)
    {
        N = random(1,MAX_NM);

        M = random(1,MAX_NM);

        out << N << " " << M << endl;

        for(int i=0; i< (M+1); i++)
        {
            out << random(0, (M - 1)) << endl;
        }

    }

    out.close();


    return 0;


}

