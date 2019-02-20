#ifndef _GRAPH_
#define _GRAPH_

#include "SList.h"
#include "Stack.h"
#include "Queue.h"
#include "HeapMin.h"
#include <limits>
using std::numeric_limits;

#define NONE -1

class Edge
{
public:

    Edge(int w, int cost = 1)
    {
        this->cost = cost;
        this->w = w;
        this->returnEdge = false;
        this->crossEdge = false;
        this->treeEdge = false;
    }
    Edge()
    {
        this->w = NONE;
        this->cost = numeric_limits<int>::max();
    }

    int cost;

    //V�rtice da extremidade, cujo essa aresta incide.
    int w;

    bool returnEdge;
    bool crossEdge;
    bool treeEdge;
};


struct Label
{
    //V�rtice de onde viemos, cujo custo do deslocamento foi cost
    int fromVertex;
    int cost;

    bool operator > ( Label other)
    {
        return cost > other.cost;
    }

    bool operator < (Label other)
    {
        return cost < other.cost;
    }

    bool operator == (Label other)
    {
        return cost == other.cost;
    }
};

//Dijkstra Node for HeapMin's operations
struct DjNode
{
    //Index of the source vertex of the label
    int srcVertex;

    Label label;

    bool operator > ( DjNode other)
    {
        return label.cost > other.label.cost;
    }

    bool operator < ( DjNode other)
    {
        return label.cost < other.label.cost;
    }

    bool operator == ( DjNode other)
    {
        return label.cost == other.label.cost;
    }
};

template <class T>
class Vertex
{
public:

    Vertex();
    ~Vertex();

    T data;

    bool visited;

    int father;

    //Label for Dijkstra algorithm, contains the cost of taveling from a "fromVertex" to this
    Label label;

    //Lista de Adjac�ncia
    SList<Edge> adjList;


};



template <class T>
class Graph
{
public:

    int nVerts;

    Vertex<T>* vertex;

    Graph(int nVerts);
    ~Graph();

    void depthSearch(int v);
    void dfsRecursive(int v, Stack<int>& pilha);

    void breadthSearch(int v);
    void bfs(int v, Queue<int>& fila );

    //Aplica Dijkstra partindo de um v�rtice inicial v.
    void applyDijkstraFrom(int v);


};

template <class T>
Vertex<T>::Vertex()
{
    this->visited = false;
    this->father = NONE;
}
template <class T>
Vertex<T>::~Vertex()
{
}


template <class T>
Graph<T>::Graph(int nVerts)
{
    this->vertex = new Vertex<T>[nVerts];
    this->nVerts = nVerts;
}
template <class T>
Graph<T>::~Graph()
{
    delete [] vertex;
}

//Depth-First-Search
template<class T>
void Graph<T>::dfsRecursive(int v,Stack<int> &pilha )
{
    this->vertex[v].visited = true;

    //cout << "Visited-> " << this->vertex[v].data << endl;
    //cin.get();

    //Visitamos todos os v�rtices adjacentes � v, fazendo uma dfs em cada um deles
    for( Node<Edge>* it = this->vertex[v].adjList.root ; it != NULL; it = it->next )
    {
        if( !this->vertex[it->data.w].visited )
        {
            it->data.treeEdge = true;

            //Adicionamos o �ndice do v�rtice na pilha(o anterior � esta adi��o � o �ndice do pai dele,se existir)
            pilha.push_front(it->data.w);

            this->dfsRecursive( it->data.w, pilha );

            delete pilha.pop_front();

        }
        //Se o n� tem pai, e se o pai dele for o v�rtice it->data.w, marque it como aresta de �rvore
        else if( pilha.root->next && pilha.root->next->data == it->data.w)
        {
            it->data.treeEdge = true;
            //cout << "Aresta de arvore! " << "(" << v << "," << it->data << ")" << "\n" << endl;
        }
        else
        {
            it->data.returnEdge = true;
            //cout << "Aresta de retorno! " << "(" << v << "," << it->data << ")" << "\n" << endl;
        }

    }


}

template<class T>
void Graph<T>::depthSearch(int v)
{
    for(int i=0; i < this->nVerts; i++)
    {
        this->vertex[i].visited = false;
    }

    //Pilha de v�rtices visitados
    Stack<int> pilha;

    pilha.push_front(v);

    dfsRecursive(v,pilha);

    delete pilha.pop_front();


}

template <class T>
void Graph<T>::breadthSearch(int v)
{
    for(int i=0; i < this->nVerts; i++)
    {
        this->vertex[i].visited = false;
    }

    Queue<int> fila;

    fila.push_back(v);
    this->vertex[v].visited = true;

    //cout << "Visited-> " << this->vertex[v].data << endl;
    //cin.get();

    Node<int>* temp = NULL;
    Node<Edge>* it = NULL;

    while( !fila.empty() )
    {
        temp = fila.pop_front();
        v = temp->data;
        delete temp;

        for(it = this->vertex[v].adjList.root ; it != NULL; it = it->next)
        {
            if( !this->vertex[it->data.w].visited )
            {
                it->data.treeEdge = true;
                fila.push_back(it->data.w);
                this->vertex[it->data.w].visited = true;
                this->vertex[it->data.w].father = v;

                //cout << "Visited-> " << this->vertex[it->data].data << endl;
                //cin.get();
            }
            //Senao, se o v�rtice de �ndice it->data for igual ao pai de v, marque it como aresta de �rvore
            else if( it->data.w == this->vertex[v].father )
            {
                it->data.treeEdge = true;
                //cout << "Aresta de arvore! " << "(" << v << "," << it->data << ")" << "\n" << endl;
            }
            else
            {
                it->data.crossEdge = true;
                //cout << "Aresta de cruzamento! " << "(" << v << "," << it->data << ")" << "\n" << endl;
            }

        }
    }
}

template <class T>
void Graph<T>::applyDijkstraFrom(int v)
{
    HeapMin<DjNode> heap((this->nVerts*(this->nVerts - 1))/2);
    DjNode temp;
    int vtemp;

    for(int i=0; i<this->nVerts; i++)
    {
        this->vertex[i].visited = false;
        this->vertex[i].label.cost = numeric_limits<int>::max();
        this->vertex[i].label.fromVertex = NONE;
    }

    //Caso Base
    this->vertex[v].label.cost = 0;
    this->vertex[v].label.fromVertex = v;
    temp.label = this->vertex[v].label;
    temp.srcVertex = v;
    heap.inserir(temp);

    //Passo indutivo
    while( heap.n>0 )
    {
        heap.remover(&temp);
        vtemp = temp.srcVertex;

        if(this->vertex[vtemp].visited) continue;

        else this->vertex[vtemp].visited = true;

        //Percorremos todas as arestas que incidem em vtemp
        for(Node<Edge>* it = this->vertex[vtemp].adjList.root; it != NULL ; it = it->next)
        {
            //Se o custo pra ir de vtemp para w for menor que o label de w
            if( ( this->vertex[vtemp].label.cost + it->data.cost ) < this->vertex[it->data.w].label.cost )
            {
                this->vertex[it->data.w].label.cost = this->vertex[vtemp].label.cost + it->data.cost;
                this->vertex[it->data.w].label.fromVertex = vtemp;

                temp.srcVertex = it->data.w;
                temp.label = this->vertex[it->data.w].label;
                heap.inserir( temp );
            }
        }

    }

}

#endif
