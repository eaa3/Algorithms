#include <iostream>
#include <cstdio>

#define EMPATE 0
#define VENCEDOR 1

using namespace std;

inline int max(const int &a,const int &b)
{
    return a>b? a : b;
}


int tabela[1001][1001];
int carta[1001];
int jogador[1001];
int S,J,C,Cont;
char buf;

int maior = 0;
int resultado = 0;
int jIndex = 0;

inline void julgar(const int &jog,const int &pontuacao)
{
    if( pontuacao > maior )
    {
        maior = pontuacao;
        resultado = VENCEDOR;
        jogador[0] = jog;
        jIndex = 1;
    }
    else if (pontuacao == maior )
    {
        resultado = EMPATE;
        jogador[jIndex++] = jog;
        if( J == 1 ) resultado = VENCEDOR;
    }


}

int main()
{
    freopen("L4Q3.in","r",stdin);
    freopen("L4Q3.out","w",stdout);

    Cont = 0;

    while( cin >> S )
    {
        cin >> J >> C;
        maior = 0;
        jIndex = 0;

        printf("Conjunto #%d\n", ++Cont);
        for(int i=0; i < J; i++)
        {
            //for(int j = 0; j <= S; j++) tabela[0][j] = 0;

            for(int k=1; k <= C; k++)
            {
                cin >> buf;

                switch(buf)
                {
                    case 'j':
                    case 'q':
                    case 'k':
                        carta[k] = 10;
                        break;
                    case 'a':
                        carta[k] = 1;
                        break;
                    default:
                        carta[k] = int(buf) - 48;
                        break;

                }


                for(int j = 1; j <= S; j++ )
                {
                    //tabela[k][0] = 0;

                    if( carta[k] <= j )
                    {
                        tabela[k][j] = max( tabela[ k - 1 ][ j ], carta[k] + tabela[ k - 1 ][ j - carta[k] ]  );
                    }
                    else
                    {
                        tabela[k][j] = tabela[k - 1][j];
                    }
                }
            }

            printf("Jogador pensando:");
            for(int j = 1; j <= S; j++){
                printf(" %d",tabela[C][j]);
            }
            printf("\n");
            julgar(i+1,tabela[C][S]);

        }



        switch(resultado)
        {
            case EMPATE:
                printf("Empate: jogadores ");
                for(int i=0;i<jIndex;i++) printf("%d ",jogador[i]);
                printf("com %d pontos\n\n",maior);
                break;
            case VENCEDOR:
                printf("Vencedor: jogador %d com %d pontos\n\n", jogador[0], maior);
                break;
            default:
                break;
        }

        //fflush(stdin);

    }


    fclose(stdout);
    //fclose(stdin);

    return 0;
}
