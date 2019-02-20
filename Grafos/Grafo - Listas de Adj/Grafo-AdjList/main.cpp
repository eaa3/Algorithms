#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{

    Graph<int> grafo(7);

    grafo.vertex[0].adjList.addLeaf(Edge(1));
    grafo.vertex[0].adjList.addLeaf(Edge(5));

    grafo.vertex[1].adjList.addLeaf(Edge(0));
    grafo.vertex[1].adjList.addLeaf(Edge(2));
    grafo.vertex[1].adjList.addLeaf(Edge(3));
    grafo.vertex[1].adjList.addLeaf(Edge(4));
    grafo.vertex[1].adjList.addLeaf(Edge(5));

    grafo.vertex[2].adjList.addLeaf(Edge(1));

    grafo.vertex[3].adjList.addLeaf(Edge(1));
    grafo.vertex[3].adjList.addLeaf(Edge(4));

    grafo.vertex[4].adjList.addLeaf(Edge(1));
    grafo.vertex[4].adjList.addLeaf(Edge(3));
    grafo.vertex[4].adjList.addLeaf(Edge(5));

    grafo.vertex[5].adjList.addLeaf(Edge(0));
    grafo.vertex[5].adjList.addLeaf(Edge(1));
    grafo.vertex[5].adjList.addLeaf(Edge(4));
    grafo.vertex[5].adjList.addLeaf(Edge(6));

    grafo.vertex[6].adjList.addLeaf(Edge(5));


    //grafo.vertex[0].color = 1;

    //cout << ( grafo.hasNeighbourWithColor(5,1) ) << endl;


    int k = 5;
    if(grafo.K_Colorivel(k)) cout << "O grafo eh " << k << " Colorivel!" << endl;
    else cout << "O grafo nao eh " << k << " Colorivel!" << endl;


    /*
    Graph<int> grafo(6);

    cout << "Loading graph..\n" << endl;

    grafo.vertex[0].adjList.addLeaf(Edge(1,2));
    grafo.vertex[0].adjList.addLeaf(Edge(2,4));

    grafo.vertex[1].adjList.addLeaf(Edge(0,2));
    grafo.vertex[1].adjList.addLeaf(Edge(2,1));
    grafo.vertex[1].adjList.addLeaf(Edge(3,10));
    grafo.vertex[1].adjList.addLeaf(Edge(4,8));

    grafo.vertex[2].adjList.addLeaf(Edge(0,4));
    grafo.vertex[2].adjList.addLeaf(Edge(1,1));
    grafo.vertex[2].adjList.addLeaf(Edge(4,5));

    grafo.vertex[3].adjList.addLeaf(Edge(1,10));
    grafo.vertex[3].adjList.addLeaf(Edge(4,2));
    grafo.vertex[3].adjList.addLeaf(Edge(5,2));

    grafo.vertex[4].adjList.addLeaf(Edge(1,8));
    grafo.vertex[4].adjList.addLeaf(Edge(2,5));
    grafo.vertex[4].adjList.addLeaf(Edge(3,2));
    grafo.vertex[4].adjList.addLeaf(Edge(5,6));

    grafo.vertex[5].adjList.addLeaf(Edge(4,6));
    grafo.vertex[5].adjList.addLeaf(Edge(3,2));


    Node<Edge>* it = NULL;

    for(int i=0; i<grafo.nVerts; i++)
    {
        grafo.vertex[i].data = i;
        cout << grafo.vertex[i].data << "-> ";
        for(it= grafo.vertex[i].adjList.root; it != NULL ; it = it->next)
        {
            cout << it->data.w <<"(" << it->data.cost << ")" << " ";
        }
        cout << endl << endl;

    }
    cout << "\nDijkstra \n" << endl;
    for(int k=0; k<grafo.nVerts; k++)
    {
        grafo.applyDijkstraFrom(k);
        cout << endl;
        for(int i=0; i < grafo.nVerts; i++)
            cout << "Tamanho do menor caminho (" << k << "," << i <<"): " << grafo.vertex[ i ].label.cost << endl;

    }

    cout << "\nBusca em largura\n" << endl;
    for(int k=0; k<grafo.nVerts; k++)
    {
        grafo.breadthSearch(k);
        cout << endl;
        for(int i=0; i < grafo.nVerts; i++)
            cout << "Tamanho do menor caminho (" << k << "," << i <<"): " << grafo.vertex[ i ].label.cost << endl;

    }


    cout << "\nPRIM'S ALGORITHM\n" << endl;
    int soma = 0;
    for(int k=0; k<grafo.nVerts; k++)
    {
        soma = 0;
        grafo.applyPrimFrom(k);
        cout << endl;
        for(int i=0; i < grafo.nVerts; i++)
        {
            cout << "AGPM partindo do vertice " << k << " (" << grafo.vertex[ i ].label.fromVertex << "," << i <<"): " << grafo.vertex[ i ].label.cost << endl;
            soma += grafo.vertex[ i ].label.cost;
        }
        cout << "Soma = " << soma << endl;


    }

    //grafo.breadthSearch(0);

    //grafo.depthSearch(0);

    //grafo.depthSearch(1);
    */


    return 0;
}
