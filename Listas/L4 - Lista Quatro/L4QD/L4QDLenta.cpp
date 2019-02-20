#include <cstdio>
#include <climits>


#define IMPOSSIVEL INT_MAX
#define VAL_MAX 100001
#define K_MAX 1001


int tabela[K_MAX][VAL_MAX];
int moeda[K_MAX];
int N,K;
int menor;
int n;
int pastResult;
int Cont;

int min(const int &a, const int &b)
{
    return a < b? a : b;
}

int main()
{
    freopen("L4QD.in","r",stdin);
    freopen("L4QD.out","w",stdout);

    while( scanf("%d %d",&N,&K) == 2 )
    {
        for(int k=0; k <= K ; k++)
        {
            if(k>0)
            {
                scanf("%d",&moeda[k]);
                moeda[k]++;
            }

            for(int j=1; j <= N; j++)
            {
                tabela[k][0] = 0;

                if( k <= 0 )
                {
                    tabela[0][j] = IMPOSSIVEL;
                }
                else
                {
                    if( moeda[k] <= j )
                    {
                        if( j%moeda[k] == 0  )
                        {
                            menor = min( j/moeda[k] , tabela[k - 1][j] );
                        }
                        else
                        {
                            menor = tabela[k - 1][j];
                        }

                        n = 1;

                        while ( ( j - moeda[k]*n ) > 0 )
                        {
                            pastResult = tabela[k - 1][j - moeda[k]*n];

                            if( pastResult != IMPOSSIVEL && (pastResult + n)   < menor  )
                            {
                                menor = pastResult + n;
                            }
                            n++;
                        }

                        tabela[k][j] = menor;

                    }
                    else
                    {
                        tabela[k][j] = tabela[k - 1][j];
                    }

                }
            }
        }

        printf("Caso #%d:",++Cont);
        if( tabela[K][N] != IMPOSSIVEL )
        {
            printf(" %d %d\n",N - tabela[K][N] ,tabela[K][N]);
        }
        else
        {
            printf(" Impossivel\n");
        }
        /*
        for(int i=0;i<=K; i++)
        {
            for(int j=0;j<=N;j++)
            {
                printf("%d ",tabela[i][j]);
            }
            printf("\n");
        }
        */
    }

    fclose(stdout);

    return 0;
}
