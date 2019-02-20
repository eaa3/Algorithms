#include <cstdio>


int F[10001];
char texto[10001];
char pattern[10001];

void preProcess(char* pattern, int np)
{

    F[0] = F[1] = 0;
    int j = 0;
    for(int i=2;i<=np;i++)
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
}

int countOcurrences(char* text,int nt, char* pattern,int np)
{

    preProcess(pattern,np);

    int j = 0;
    int count = 0;
    int i = 0;

    while(i < nt )
    {
        while(true)
        {
            if( pattern[j] == text[i] )
            {
                j++;
                i++;

                if( j == np )
                {
                    printf("%d %d\n", (i - np), i - 1);

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

    return count;



}

int main()
{
    freopen("L4Q1.in","r",stdin);
    freopen("L4Q1.out","w",stdout);

    int N,M,K;

    while(scanf("%d",&K)== 1){

    for(int i=0;i<K;i++)
    {
        scanf("%d %d", &N,&M);
        scanf("%s",pattern);
        scanf("%s",texto);

        N = countOcurrences(texto,M,pattern,N);

        printf("%d\n\n",N);

    }
    }

    fclose(stdout);
    return 0;

}

