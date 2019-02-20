#include <cstdio>
#include "Graph.h"

int main()
{
    freopen("L3Q1.in","r",stdin);
    freopen("L3Q1.out","w",stdout);

    int N,M,K,A,B,seconds;
    int contCaso = 0;
    while( scanf("%d %d %d",&N,&M,&K) == 3 )
    {
        if(N==0 && M==0 && K==0)
        {
            break;
        }
        else
        {

            Graph<int> grafo(N);

            for(int i=0; i<M; i++)
            {
                scanf("%d %d",&A,&B);

                grafo.vertex[A - 1].adjVerts.addLeaf(B - 1);
                grafo.vertex[B - 1].adjVerts.addLeaf(A - 1);


            }
            /*
            Node<int>* it = NULL;

            for(int i=0; i<grafo.nVerts; i++)
            {
                cout << grafo.vertex[i].data << "-> ";
                for(it= grafo.vertex[i].adjVerts.root; it != NULL ; it = it->next)
                {
                    cout << it->data << " ";
                }
                cout << endl << endl;

            }*/

            for(int i=0; i<K; i++)
            {
                scanf("%d",&A);
                grafo.vertex[A - 1].hasRabbit = true;
            }

            seconds = grafo.breadthSearch(0,K);
            contCaso++;
            printf("Caso #%d: %d\n",contCaso,seconds);
        }
    }


    fclose(stdout);

    return 0;
}
