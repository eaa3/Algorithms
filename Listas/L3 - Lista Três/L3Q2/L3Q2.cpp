#include <cstdio>
#include <limits>
using std::numeric_limits;

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

};

template <class T>
class Stack : public SList<T>
{
    public:

        Stack();
        ~Stack();

        void push_front(T data);
        Node<T>* pop_front();

        Node<T>* getRoot();


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

template <class T>
class HeapMin
{
    public:

        T *array;
        int n;
        int size;

        void constroi();
        void descer(int i);
        void subir(int i);
        bool inserir(T chave);

        //Coloca a chave retirada no apontador passado como parâmetro
        bool remover(T *chave);

        int getSize();

        void clear();
        void init(int size);

        HeapMin(int size);
        ~HeapMin();

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
        this->cost = numeric_limits<int>::max();
    }

    int cost;

    //Vértice da extremidade, cujo essa aresta incide.
    int w;

    bool returnEdge;
    bool crossEdge;
    bool treeEdge;
};


struct Label
{
    //Vértice de onde viemos, cujo custo do deslocamento foi cost
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


};

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

}

template<class T>
Node<T>* SList<T>::removeRoot()
{
    Node<T>* removedNode = this->root;

    if(this->root)
    {
        this->root = this->root->next;

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
Stack<T>::Stack() : SList<T>()
{

}
template <class T>
Stack<T>::~Stack()
{

}

template <class T>
void Stack<T>::push_front(T data)
{
    this->addRoot(data);
}

template <class T>
Node<T>* Stack<T>::pop_front()
{
    return this->removeRoot();
}

template <class T>
Node<T>* Stack<T>::getRoot()
{
    return this->root;
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
            //Senao, se o vértice de índice it->data for igual ao pai de v, marque it como aresta de árvore
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

        else this->vertex[temp.srcVertex].visited = true;

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

template <class T>
HeapMin<T>::HeapMin(int size)
{
    this->array = new T[size + 1];
    this->size = size + 1;
    this->n = 0;
}

template <class T>
HeapMin<T>::~HeapMin()
{
    this->clear();
}

template <class T>
void HeapMin<T>::clear()
{
    delete [] this->array;
    this->array = NULL;
}

template <class T>
void HeapMin<T>::init(int size)
{
    if(!this->array)
    {
        this->array = new T[size + 1];
        this->size = size + 1;
        this->n = 0;
    }

}

template <class T>
void HeapMin<T>::descer(int i)
{
    int esq = 2*i;
    int dir = 2*i + 1;
    int menor = esq;
    T temp;

    //Se ele ao menos tiver um filho à esquerda
    if( esq <= this->n )
    {
        //Se ele tiver um filho à direita tbm...
        if( esq < this->n )
        {
            if( this->array[dir] < this->array[esq] )
            {
                menor = dir;
            }
        }

        if( this->array[i] > this->array[menor] )
        {
            temp = this->array[i];
            this->array[i] = this->array[menor];
            this->array[menor] = temp;

            this->descer(menor);
        }
    }
}

template <class T>
void HeapMin<T>::subir(int i)
{
    int pai = i/2;
    T temp;

    //Se o nó de índice i tiver pai...
    if( pai >= 1)
    {
        if( this->array[i] < this->array[pai] )
        {
            temp = this->array[pai];

            this->array[pai] = this->array[i];
            this->array[i] = temp;

            this->subir(pai);
        }
    }
}

template <class T>
void HeapMin<T>::constroi()
{
    for(int i = this->n/2 ; i>=1 ; i-- )
    {
        this->descer(i);
    }
}

template <class T>
bool HeapMin<T>::inserir(T chave)
{
    if( (this->n + 1) < this->size )
    {
        this->array[++this->n] = chave;
        subir(this->n);

        return true;
    }

    return false;
}

template <class T>
bool HeapMin<T>::remover(T *chave)
{
    if(chave)
    {
        //Se existirem chaves no heap
        if( this->n > 0 )
        {
            *chave = this->array[1];

            this->array[1] = this->array[n];
            this->n--;

            this->descer(1);

            return true;
        }

    }

    return false;
}

template <class T>
int HeapMin<T>::getSize()
{
    return this->size - 1;
}


