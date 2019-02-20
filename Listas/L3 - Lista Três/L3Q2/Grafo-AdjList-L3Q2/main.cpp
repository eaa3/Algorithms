#include <cstdio>
#include "Graph.h"


int main()
{
    freopen("L3Q2.in","r",stdin);
    freopen("L3Q2.out","w",stdout);
    int N,D,C;
    int A,B,W,Custo;
    int contCaso = 0;


    while(scanf("%d %d %d",&N,&D,&C) == 3)
    {
        Graph<int> grafo(N);

        for(int i=0; i < C; i++)
        {
            scanf("%d %d %d",&A,&B,&W);

            W < D? Custo = 0 : Custo = 1; //Custo = feijões
            grafo.vertex[A - 1].adjList.addLeaf(Edge(B - 1, Custo));
            grafo.vertex[B - 1].adjList.addLeaf(Edge(A - 1, Custo));
        }

        grafo.applyDijkstraFrom(0);

        printf("Caso #%d: %d\n", ++contCaso, grafo.vertex[N - 1].label.cost );
    }

    fclose(stdout);
    return 0;
}
