#include <cstdio>
#include <climits>

#define IMPOSSIVEL INT_MAX - 1
#define VAL_MAX 100001
#define K_MAX 1001


int tabela[VAL_MAX];
int moeda[K_MAX];
int N,K;
int Cont;

int main()
{
    freopen("L4QD.in","r",stdin);
    freopen("L4QD.out","w",stdout);

    while( scanf("%d %d",&N,&K) == 2 )
    {

        for(int k=0; k< K; k++)
        {
            scanf("%d",&moeda[k]);
            moeda[k]++;
        }

        for(int s = 0; s <= N; s++) tabela[s] = IMPOSSIVEL;
        tabela[0] = 0;

        for(int s=1; s<=N; s++)
        {

            for(int k=0; k < K ; k++)
            {

                if( moeda[k]<=s && (tabela[s - moeda[k]] + 1) < tabela[s] )
                {
                    tabela[s] = (tabela[s - moeda[k]] + 1);
                }

            }
        }

        printf("Caso #%d:",++Cont);
        if( tabela[N] != IMPOSSIVEL )
        {
            printf(" %d %d\n", N - tabela[N], tabela[N]);
        }
        else
        {
            printf(" Impossivel\n");
        }

    }

    fclose(stdout);

    return 0;
}

