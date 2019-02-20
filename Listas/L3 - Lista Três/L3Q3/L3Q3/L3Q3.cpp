#include <cstdio>

struct Edge
{
    int a,b,c;

    bool operator < ( Edge other)
    {
        return c < other.c;
    }
    bool operator > ( Edge other )
    {
        return c > other.c;
    }
};

inline int min(int a,int b)
{
    if(a<b) return a;
    else return b;
}



class Elemento
{
public:

    Elemento()
    {
        this->rep = NULL;
        this->rank = 0;
    }


    Elemento(int dado)
    {
        this->dado = dado;
        this->rank = 0;
        this->rep = NULL;
    }


    int rank;
    int dado;
    Elemento* rep;


};


void makeSet(Elemento* x)
{
    x->rep = x;
}


Elemento* findSet(Elemento* x)
{
    //Representante
    Elemento* rep = NULL;

    if( x->rep == x)
    {
        rep = x;
    }
    else
    {
        rep = findSet(x->rep);

        //Path Compression
        x->rep = rep;
        x->dado = rep->dado;
    }

    return rep;
}


void link(Elemento* x, Elemento* y)
{
    //Procura-se unir a árvore de menor rank à árvore de maior rank

    if( x->rank < y->rank )
    {
        x->rep = y->rep;

    }
    else if( x->rank > y->rank )
    {
        y->rep = x->rep;
    }
    else
    {
        x->rep = y->rep;

        x->rank++;
    }

}


void sUnion(Elemento* x, Elemento* y)
{
    link( findSet(x) , findSet(y) );
}


inline void swap( Edge& a, Edge& b )
{
    Edge temp = a;
    a = b;
    b = temp;
}



void descer(int i, Edge array[],int n)
{
    int esq = 2*i;
    int dir = 2*i + 1;

    int maior = esq;

    if( esq <= n )
    {
        if( esq < n )
        {
            if( array[dir] > array[esq] )
                maior = dir;
        }

        if( array[i] < array[maior] )
        {
            swap(array[i],array[maior]);
            descer(maior,array,n);
        }

    }

}
void makeHeap(Edge array[],int n)
{
    for(int i = n/2 ; i>=1 ; i-- )
    {
        descer(i,array,n);
    }
}
void heapSort(Edge array[],int size)
{
    makeHeap(array,size);

    for(int i=size; i > 1; i--)
    {
        descer(1,array,i);
        swap(array[1],array[i]);
    }
}

struct infoKruskal
{
    int nConexComp;

    //Somatório do custo das árvores de peso mínimo de todos os componentes conexos
    int sumAGPM;
};

infoKruskal AGMP_Kruskal(Elemento vertex[],int &sizeV,Edge edge[],int &sizeE)
{
    infoKruskal info;
    info.nConexComp = sizeV;
    info.sumAGPM = 0;
    int v,w;
    Elemento* repX=NULL;
    Elemento* repY=NULL;

    for(int i=1; i <= sizeV; i++)
    {
        makeSet( vertex + i );
        vertex[i].dado = i;
    }

    heapSort(edge,sizeE);

    for(int i=1; i <= sizeE; i++ )
    {
        v = edge[i].a;
        w = edge[i].b;
        //Se a aresta i liga os vértices mas eles ainda não fazem parte do mesmo comp Conexe, então conecte eles
        repX = findSet(vertex + v);
        repY = findSet(vertex + w);

        if( repX != repY )
        {
            info.nConexComp--;
            info.sumAGPM += edge[i].c;

            sUnion(repX,repY);

            repX->dado = min(repY->dado, repX->dado);
            repY->dado = repX->dado;
        }
    }

    return info;
}


int main()
{
    freopen("L3Q3.in","r",stdin);
    freopen("L3Q3.out","w",stdout);

    int N,M;
    Elemento *vertex = NULL;
    Edge *edge = NULL;
    Elemento *elemTemp = NULL;
    int pastComp = 0;
    infoKruskal info;
    int contCaso = 0;

    while( scanf("%d %d",&N,&M) == 2 )
    {
        if( N!=0 && M!=0)
        {
            vertex = new Elemento[N + 1];
            edge = new Edge[M + 1];
            for(int i=1; i <= M ; i++)
            {
                scanf("%d %d %d",&edge[i].a,&edge[i].b,&edge[i].c);
            }

            info = AGMP_Kruskal(vertex,N,edge,M);

            printf("Caso #%d: %d %d\n",++contCaso,info.sumAGPM,info.nConexComp);

            pastComp = 1;
            for(int i=1; i <= N ; i++)
            {
                elemTemp = findSet( vertex + i );

                //Se número da vila(elemTemp) estiver errado quanto a i, conserte
                if( elemTemp->dado > pastComp )
                {
                    elemTemp->dado = pastComp + 1;
                    pastComp = pastComp + 1;
                }

                printf("%d",elemTemp->dado);
                if(i!=(N)) printf(" ");
            }
            printf("\n");


            delete [] vertex;
            delete [] edge;
            pastComp = 0;
        }
        else break;
    }

    fclose(stdout);

    return 0;
}


