#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;


stringstream buf;


int* preProcess(string &pattern)
{
    int *F = new int[pattern.size() + 1];

    F[0] = F[1] = 0;
    int j = 0;
    for(int i=2;i<=pattern.size();i++)
    {
        j = F[i - 1];

        while(true)
        {
            if( pattern[j] == pattern[i - 1])
            {
                F[i] = j + 1;
                break;
            }

            if( j == 0 )
            {
                F[i] = 0;
                break;
            }

            j = F[j];
        }

    }


    return F;
}

int countOcurrences(string &text, string& pattern)
{

    int *F = preProcess(pattern);

    int j = 0;
    int count = 0;
    int i = 0;

    //cout << "Funcao F " << endl;
    //for(int i=0; i <= pattern.size(); i++) cout << F[i] << " ";

    while(i < text.size() )
    {
        while(true)
        {
            if( pattern[j] == text[i] )
            {
                j++;
                i++;

                if( j == pattern.size() )
                {
                    buf << i - j << " " << i - 1 << endl;
                    count++;
                    j = F[j];
                    break;
                }
            }
            else if( j == 0 )
            {
                i++;
                break;
            }
            else
            {
                j = F[j];
                break;
            }
        }
    }

    delete []F;
    F = NULL;
    return count;



}

int main()
{
    freopen("L4Q1.in","r",stdin);
    freopen("L4Q1.out","w",stdout);

    string texto,pattern;
    int* F = NULL;
    int N,M,K;

    while(cin >> K){

    for(int i=0;i<K;i++)
    {
        cin >> N >> M;
        cin >> pattern;
        cin >> texto;

        N = countOcurrences(texto,pattern);

        cout << buf.str();
        cout << N << endl <<  endl;

        buf.str("");

    }
    }



    /*
   // F = preProcess(pattern);

    int n = countOcurrences(texto,pattern);

    cout << "\nExistem " << n <<  " ocorrencias do padrao " << " \"" << pattern << "\"" << endl;

    cin.get();


    delete [] F;
    */
    fclose(stdout);
    return 0;

}

