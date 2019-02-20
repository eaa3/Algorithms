#ifndef _GRAPH_
#define _GRAPH_

#include "SList.h"
#include "Stack.h"
#include "Queue.h"
#include "HeapMin.h"
#include <limits>
#include <iostream>
using namespace std;

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

    //Vértice da extremidade, cujo essa aresta incide.
    int w;

    bool returnEdge;
    bool crossEdge;
    bool treeEdge;

    bool operator > ( Edge &other )
    {
        return this->cost > other.cost;
    }

    bool operator < ( Edge &other )
    {
        return this->cost < other.cost;
    }

    bool operator == ( Edge &other )
    {
        return this->cost == other.cost;
    }
};


struct Label
{
    //Vértice de onde viemos,ao sairmos andando pelo grafo, cujo custo do deslocamento foi cost
    int fromVertex;
    int cost;

    bool operator > ( Label &other)
    {
        return cost > other.cost;
    }

    bool operator < (Label &other)
    {
        return cost < other.cost;
    }

    bool operator == (Label &other)
    {
        return cost == other.cost;
    }
};

//Node for HeapMin's operations
struct GHeapNode
{
    //Index of the source vertex of the label
    int srcVertex;

    Label label;

    bool operator > ( GHeapNode &other)
    {
        return label.cost > other.label.cost;
    }

    bool operator < ( GHeapNode &other)
    {
        return label.cost < other.label.cost;
    }

    bool operator == ( GHeapNode &other)
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

    //Label for Dijkstra algorithm, contains the cost of taveling from a "fromVertex" to this
    Label label;

    //Lista de Adjacência
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

    //Aplica Dijkstra partindo de um vértice inicial v.
    void applyDijkstraFrom(int v);

    //Aplica o algoritmo Prim para AGPM  a partir de um vértice inicial v
    void applyPrimFrom(int v);


};

template <class T>
Vertex<T>::Vertex()
{
    this->visited = false;
    //this->label.cost = 0;
    //this->label.fromVertex = NONE;
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

    //Visitamos todos os vértices adjacentes à v, fazendo uma dfs em cada um deles
    for( Node<Edge>* it = this->vertex[v].adjList.root ; it != NULL; it = it->next )
    {
        if( !this->vertex[it->data.w].visited )
        {
            it->data.treeEdge = true;

            //Adicionamos o índice do vértice na pilha(o anterior à esta adição é o índice do pai dele,se existir)
            pilha.push_front(it->data.w);

            this->dfsRecursive( it->data.w, pilha );

            delete pilha.pop_front();

        }
        //Se o nó tem pai, e se o pai dele for o vértice it->data.w, marque it como aresta de árvore
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

    //Pilha de vértices visitados
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
        this->vertex[i].label.fromVertex = NONE;
        this->vertex[i].label.cost = 0;
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
                this->vertex[it->data.w].label.fromVertex = v;
                this->vertex[it->data.w].label.cost = this->vertex[v].label.cost + 1;

                //cout << "Visited-> " << this->vertex[it->data].data << endl;
                //cin.get();
            }
            //Senao, se o vértice de índice it->data for igual ao pai de v, marque it como aresta de árvore
            else if( it->data.w == this->vertex[v].label.fromVertex )
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
    HeapMin<GHeapNode> heap((this->nVerts*(this->nVerts - 1))/2);
    GHeapNode temp;
    int vtemp;

    for(int i=0; i<this->nVerts; i++)
    {
        this->vertex[i].visited = false;
        this->vertex[i].label.cost = numeric_limits<int>::max();
        this->vertex[i].label.fromVertex = NONE;
    }
    cout << endl;

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

        //Se esse vértice já foi visitado, eu não preciso ver a lista de adjacência dele de novo.
        if(this->vertex[vtemp].visited) continue;

        this->vertex[vtemp].visited = true;

        //Percorremos todas as arestas que incidem em vtemp
        for(Node<Edge>* it = this->vertex[vtemp].adjList.root; it != NULL ; it = it->next)
        {
            //Se o custo pra ir de vtemp para w for menor que o label de w e w já não tiver sido visitado antes ( Um algoritmo guloso nunca muda suas decisões passadas )
            if( ( this->vertex[vtemp].label.cost + it->data.cost ) < this->vertex[it->data.w].label.cost && !this->vertex[it->data.w].visited )
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

template <class T>
void Graph<T>::applyPrimFrom(int v)
{
    HeapMin<GHeapNode> heap((this->nVerts*(this->nVerts - 1))/2);
    GHeapNode temp;
    int vtemp;

    for(int i=0; i<this->nVerts; i++)
    {
        this->vertex[i].visited = false;
        this->vertex[i].label.cost = numeric_limits<int>::max();
        this->vertex[i].label.fromVertex = NONE;

    }
    cout << endl;

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

        //Se esse vértice já foi visitado, eu não preciso ver a lista de adjacência dele de novo.
        if(this->vertex[vtemp].visited) continue;

        this->vertex[vtemp].visited = true;

        //Percorremos todas as arestas que incidem em vtemp
        for(Node<Edge>* it = this->vertex[vtemp].adjList.root; it != NULL ; it = it->next)
        {
            //Se o custo da aresta it->data.cost for menor que o custo do label do vértice it->data.w ... E o vértice w ainda nao foi visitado
            if(  it->data.cost < this->vertex[it->data.w].label.cost && !this->vertex[it->data.w].visited )
            {
                this->vertex[it->data.w].label.cost = it->data.cost;
                this->vertex[it->data.w].label.fromVertex = vtemp;

                temp.srcVertex = it->data.w;
                temp.label = this->vertex[it->data.w].label;
                heap.inserir( temp );
            }
        }

    }

}



#endif
