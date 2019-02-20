
#include <cstdio>
#define NOFATHER -1

template <class T>
class Node
{
public:
    T data;
    int cost;

    bool returnEdge;
    bool crossEdge;
    bool treeEdge;

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
    this->returnEdge = false;
    this->crossEdge = false;
    this->treeEdge = false;

}

template<class T>
Node<T>::Node(T data)
{
    this->next = NULL;
    this->cost = 1;
    this->returnEdge = false;
    this->crossEdge = false;
    this->treeEdge = false;
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
