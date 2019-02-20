#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

const int MAX_ALUNOS = 200;
const int MOTORISTA = 0;

struct Aluno
{
    int indicacao;
    bool embarcou;
};

Aluno aluno[MAX_ALUNOS];

int main()
{
    ifstream in("L0Q4.in");
    ofstream out("L0Q4.out");
    int N,M,count;
    N = M = count =  0;

    while( in >> N >> M )
    {


        for(int i=0; i<(M+1) ; i++)
        {
            in >> aluno[i].indicacao;

            aluno[i].embarcou = false;

        }

        int cracha = aluno[MOTORISTA].indicacao;

        out << "Onibus #" << ++count << endl;

        for(int i=0; i<N && i<M ; i++)
        {

            if( !cracha || aluno[cracha].embarcou)
            {
                int k = 1;
                while(aluno[k].embarcou)
                {
                    k++;
                }

                cracha = k;

            }

            out << cracha <<" ";

            aluno[cracha].embarcou = true;
            cracha = aluno[cracha].indicacao;

        }

        out << endl << endl;



    }

    out.close();
    in.close();

    return 0;
}



