#include <fstream>

using std::endl;
using std::ifstream;
using std::ofstream;

const int MAX_SIZE = 101;

long long C[MAX_SIZE*MAX_SIZE];
//Carregando o triângulo de pascal...
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

int main()
{
    cacheComb();

    ofstream out("L0QD.out");

    ifstream in("L0QD.in");


    int N,M;

    N = M = 0;


    while( in >> N >> M )
    {

        out << C[N*MAX_SIZE + M] << endl;

    }

    out.close();
    return 0;
}
