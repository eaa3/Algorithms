#include <cstdio>

#define NONE -1

template <class T>
class Node
{
public:
    T data;

    Node* next;

    Node(T data);
    Node();
    ~Node();

};

template <class T>
class SList
{
public:

    Node<T>* root;
    Node<T>* leaf;

    SList();
    ~SList();

    void addRoot(T data);
    void addLeaf(T data);

    Node<T>* removeRoot();
    Node<T>* removeLeaf();
    Node<T>* remove(T data);
    int size;

};

template <class T>
class Queue : public SList<T>
{
    public:

        Queue();
        ~Queue();

        void push_back(T data);
        Node<T>* pop_front();

        bool empty();

        Node<T>* getRoot();


};

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
        //this->cost = numeric_limits<int>::max();
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

    //Color for coloring algorithm
    int color;

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

    //Verifica se o grafo é K-Colorível
    bool K_Colorivel(int k);
    bool K_ColorivelRec(int k, int v);



    //Verifica se o vértice v tem um vizinho w com a cor c
    bool hasNeighbourWithColor(int c,int v);


};

int N,M;
int A,B;
int K;
int Cont = 0;

int main()
{
    freopen("L4Q2.in","r",stdin);
    freopen("L4Q2.out","w",stdout);

    while ( scanf("%d %d",&N,&M) == 2 )
    {
        Graph<int> grafo(N);

        for(int i=0;i<M;i++)
        {
            scanf("%d %d",&A,&B);

            grafo.vertex[A - 1].adjList.addLeaf(Edge(B-1));
            grafo.vertex[B - 1].adjList.addLeaf(Edge(A-1));

        }

        K = 1;

        while ( true )
        {
            if( grafo.K_Colorivel(K) ) break;

            K++;
        }

        printf("Conjunto #%d\n",++Cont);
        printf("%d\n",K);

    }

    fclose(stdout);



    /*
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


    int k = 2;
    if(grafo.K_Colorivel(k)) cout << "O grafo eh " << k << " Colorivel!" << endl;
    else cout << "O grafo nao eh " << k << " Colorivel!" << endl;
    */

    return 0;

}


template <class T>
Vertex<T>::Vertex()
{
    this->visited = false;
    this->color = 0;
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

/*
template<class T>
void print(SList<T> &list)
{
    Node<T>* iterator = list.root;

    cout << endl;

    while(iterator)
    {
        cout << iterator->data << endl;
        iterator = iterator->next;

    }

}
*/
template <class T>
Node<T>::Node()
{
    this->next = NULL;
    this->cost = 1;

}

template<class T>
Node<T>::Node(T data)
{
    this->next = NULL;
    this->data = data;

}

template<class T>
Node<T>::~Node()
{
   // cout << "Fui destruido" << endl;

}

template<class T>
SList<T>::SList()
{
    this->root = NULL;
    this->leaf = NULL;
    this->size = 0;
}

template<class T>
SList<T>::~SList()
{
    Node<T>* current = this->root;
    Node<T>* previous = NULL;

    while(current)
    {
        previous = current;

        current = current->next;

        delete previous;
    }
    this->size = 0;
}

template<class T>
void SList<T>::addRoot(T data)
{
    Node<T>* newNode = new Node<T>(data);

    if(!this->root)
    {
        this->root = newNode;
        this->leaf = newNode;
    }
    else
    {
        newNode->next = this->root;
        this->root = newNode;
    }

    this->size++;
}

template<class T>
void SList<T>::addLeaf(T data)
{
    Node<T>* newNode = new Node<T>(data);

    if(!this->root)
    {
        this->root = newNode;
        this->leaf = newNode;
    }
    else
    {
        this->leaf->next = newNode;
        this->leaf = newNode;
    }

    this->size++;

}

template<class T>
Node<T>* SList<T>::removeRoot()
{
    Node<T>* removedNode = this->root;

    if(this->root)
    {
        this->root = this->root->next;
        this->size--;

    }


    return removedNode;
}

template <class T>
Node<T>* SList<T>::removeLeaf()
{
    Node<T>* removedNode = this->leaf;

    if(this->leaf)
    {
        Node<T>* iterator = this->root;

        if(this->leaf == this->root)
        {
            this->root = NULL;
            this->leaf = NULL;
        }
        else
        {
            while(iterator->next != this->leaf)
            {
                iterator = iterator->next;
            }

            iterator->next = NULL;
            this->leaf = iterator;

        }
        this->size--;

    }

    return removedNode;

}
template <class T>
Node<T>* SList<T>::remove(T data)
{
    Node<T>* removedNode = NULL;

    if(this->root)
    {
        if(this->root->data == data)
        {
            this->root->data;
            removedNode = this->removeRoot();
        }
        else
        {
            //Sentinela
            this->addLeaf(data);

            Node<T>* current = this->root;
            Node<T>* previous = NULL;

            while( current->data != data )
            {
                previous = current;

                current = current->next;
            }

            if(current->next)
            {
                this->removeLeaf();

                removedNode = current;

                previous->next = current->next;

                this->size--;
            }
            else
            {
                this->removeLeaf();
            }

        }

    }

    return removedNode;
}

template <class T>
bool Graph<T>::hasNeighbourWithColor(int c,int v)
{
    for(Node<Edge>* it = this->vertex[v].adjList.root; it != NULL ; it = it->next)
    {
        if( this->vertex[it->data.w].color == c ) return true;
    }

    return false;
}

template <class T>
bool Graph<T>::K_Colorivel(int k)
{

    if( k >= this->nVerts ) return true;

    for(int i=0; i<this->nVerts; i++)
    {
        this->vertex[i].color = 0;
    }
    //cout << "Pintando o vertice " << 0 << endl;
    //cout << "Atribuiu cor " << 1 << " Ao vertice "<< 0 << endl;
    //cin.get();
    this->vertex[0].color = 1;

    return this->K_ColorivelRec(k,0);
}

template <class T>
bool Graph<T>::K_ColorivelRec(int k,int v)
{
    if( v >= (this->nVerts - 1) ) return true;

    int z = v + 1;

    //cout << "Pintando o vertice " << z << endl;
    //cin.get();

    for(int c=1; c<=k; c++)
    {
        if(!this->hasNeighbourWithColor(c,z))
        {
            //cout << "Atribuiu cor " << c << " Ao vertice "<< z << endl;
            //cin.get();
            this->vertex[z].color = c;

            if( K_ColorivelRec(k,z) ) return true;
        }
    }

    this->vertex[z].color = 0;

    //cout << "BackTrack" << endl;
    //cin.get();
    return false; //BackTrack
}

template <class T>
Queue<T>::Queue() : SList<T>()
{

}
template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::push_back(T data)
{
    this->addLeaf(data);
}

template <class T>
Node<T>* Queue<T>::pop_front()
{
    return this->removeRoot();
}

template <class T>
Node<T>* Queue<T>::getRoot()
{
    return this->root;
}

template <class T>
bool Queue<T>::empty()
{
    return this->root == NULL;
}
