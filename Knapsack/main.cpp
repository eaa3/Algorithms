#include <cstdio>

struct Item
{
    int valor;
    int peso;
};

int max(int a, int b)
{
    if( a > b ) return a;
    else return b;
}

void knapSack(int* &tabela,int capacidade, Item* item, int nItem)
{
    int ti = nItem + 1;
    int tj = capacidade + 1;
    tabela = new int[ti*tj];

    for(int j=0; j<tj; j++) tabela[0*tj + j] = 0;


    for(int i=1; i<ti; i++)
    {
        for(int j=1; j<tj;j++)
        {
            tabela[i*tj + 0] = 0;

            if( item[i - 1].peso <= j )
            {
                tabela[i*tj + j] = max( tabela[(i - 1)*tj + j] , item[i - 1].valor + tabela[(i - 1)*tj + ( j - item[i - 1].peso )] );
            }
            else
            {
                tabela[i*tj + j] = tabela[(i - 1)*tj + j];
            }

        }
    }



}

int main()
{
    Item item[] = {{2,4},{1,2},{3,1},{4,2} };
    int * tabela = NULL;

    knapSack(tabela,5,item,4);


    if(tabela != NULL)
    {
        int ti = 4 + 1;
        int tj = 5 + 1;
        for(int i=0; i < ti; i++)
        {
            for(int j=0;j<tj;j++)
            {
                printf(" %d ",tabela[i*tj + j]);
            }
            printf("\n");
        }

        delete [] tabela;
    }


    return 0;

}
