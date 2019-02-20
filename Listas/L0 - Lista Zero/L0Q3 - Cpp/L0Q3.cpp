#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

const int MAX_SIZE = 1000000;

int A[MAX_SIZE];
int iA,jA;

int B[MAX_SIZE];
int iB,jB;

ifstream in("L0Q3.in");
ofstream out("L0Q3.out");

inline void loadMatrix(int M[],int size)
{
    for(int k=0; k< size ; k++)
    {
        in >> M[k];
    }
}

int main()
{
    int count = 0;

    while( !in.eof() )
    {
        in >> iA >> jA;
        loadMatrix(A,iA*jA);

        in >> iB >> jB;
        loadMatrix(B,iB*jB);

        if(jA != iB && !in.eof() )
        {
            out << "Conjunto #" << ++count << "\n" << -1 << "\n" << endl;
        }
        else if(!in.eof())
        {
            int val = 0;

            out << "Conjunto #" << ++count << endl;

            for(int i=0; i< iA ; i++)
            {
                for(int k=0;k<jB;k++)
                {
                    for(int j=0; j<jA ; j++)
                    {
                          val += A[i*jA + j]*B[j*jB + k];
                    }

                    if(k != (jB - 1)) out << val << " ";
                    else out << val;

                    val = 0;
                }

                out << endl;

            }

            out << endl;


        }





    }

    out.close();

    return 0;

}
