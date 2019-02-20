#ifndef _GRAPH_
#define _GRAPH_

#include "SList.h"
#include "Stack.h"
#include "Queue.h"

#define NOFATHER -1


template <class T>
class Vertex
{
public:

    Vertex();
    ~Vertex();

    T data;

    bool visited;
    bool hasRabbit;
    int seconds;

    int father;

    //Lista de Adjacência
    SList<int> adjVerts;


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


    //Irá retornar o número mínimo de segundos que o mágico irá precisar pra pegar todos os coelhos
    int breadthSearch(int v,int salasComCoelhos);


};


template <class T>
Vertex<T>::Vertex()
{
    this->visited = false;
    this->father = NOFATHER;
    this->hasRabbit = false;
    this->seconds = 0;
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

template<class T>
void Graph<T>::dfsRecursive(int v,Stack<int> &pilha )
{
    this->vertex[v].visited = true;

    //cout << "Visited-> " << this->vertex[v].data << endl;
    //cin.get();

    //Visitamos todos os vértices adjacentes à v, fazendo uma dfs em cada um deles
    for( Node<int>* it = this->vertex[v].adjVerts.root ; it != NULL; it = it->next )
    {
        if( !this->vertex[it->data].visited )
        {
            it->treeEdge = true;

            //Adicionamos o índice do vértice na pilha(o anterior à esta adição é o índice do pai dele)
            pilha.push_front(it->data);

            this->dfsRecursive( it->data, pilha );

            delete pilha.pop_front();

        }
        else if( pilha.root->next && pilha.root->next->data == it->data)
        {
            it->treeEdge = true;
            //cout << "Aresta de arvore! " << "(" << v << "," << it->data << ")" << "\n" << endl;
        }
        else
        {
            it->returnEdge = true;
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

    //Pilha de índices do array de vértices
    Stack<int> pilha;

    pilha.push_front(v);

    dfsRecursive(v,pilha);

    delete pilha.pop_front();


}

template <class T>
int Graph<T>::breadthSearch(int v,int salasComCoelhos)
{
    int seconds = 0;
    for(int i=0; i < this->nVerts; i++)
    {
        this->vertex[i].visited = false;
    }

    Queue<int> fila;

    fila.push_back(v);
    this->vertex[v].visited = true;

    if( this->vertex[v].hasRabbit )
    {
        this->vertex[v].hasRabbit = false;
        salasComCoelhos--;
    }

    //cout << "Visited-> " << this->vertex[v].data << endl;
    //cin.get();

    Node<int>* it;

    while( !fila.empty() && salasComCoelhos>0 )
    {

        it = fila.pop_front();
        v = it->data;
        delete it;

        for(it = this->vertex[v].adjVerts.root ; it != NULL && salasComCoelhos>0 ; it = it->next)
        {
            if( !this->vertex[it->data].visited )
            {
                it->treeEdge = true;

                fila.push_back(it->data);

                this->vertex[it->data].visited = true;
                this->vertex[it->data].father = v;
                this->vertex[it->data].seconds = this->vertex[v].seconds + 1;

                if( this->vertex[it->data].hasRabbit )
                {
                    this->vertex[it->data].hasRabbit = false;
                    salasComCoelhos--;
                    seconds = this->vertex[it->data].seconds ;
                    //cout << "Tem coelhos [" << salasComCoelhos << "]" << " Nivel " << seconds<< endl;

                }

                //cout << "Visited-> " << this->vertex[it->data].data << endl;
                //cin.get();
            }
            else if( it->data == this->vertex[v].father )
            {
                it->treeEdge = true;
                //cout << "Aresta de arvore! " << "(" << v << "," << it->data << ")" << "\n" << endl;
            }
            else
            {
                it->crossEdge = true;
                //cout << "Aresta de cruzamento! " << "(" << v << "," << it->data << ")" << "\n" << endl;
            }

        }
    }

    return seconds;
}

#endif
