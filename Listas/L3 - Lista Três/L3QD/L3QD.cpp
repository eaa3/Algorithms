#include <cstdio>
#include <conio.h>
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
        this->forcaDeus = 0;
        this->tam = 1;
    }


    Elemento(int forcaDeus)
    {
        this->forcaDeus = forcaDeus;
        this->rank = 0;
        this->rep = NULL;
        this->tam = 1;
    }


    int rank;
    int forcaDeus;
    Elemento* rep;
    bool added; // Has already been added or not
    int tam; // tamamnho do grupo o qual este elemento pertence


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
        x->forcaDeus = rep->forcaDeus;
        x->tam = rep->tam;
        x->added = rep->added;
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

struct Grupo
{
    int F; // Força do Deus
    int T; // Número de pessoas no grupo
    bool vencido;

    bool operator < ( Grupo other )
    {
        return (F + T) < (other.F + other.T);
    }
    bool operator > ( Grupo other )
    {
        return (F + T) > (other.F + other.T);
    }
    bool operator >= ( Grupo other )
    {
        return (F + T) >= (other.F + other.T);
    }

    bool operator <= ( Grupo other )
    {
        return (F + T) <= (other.F + other.T);
    }
    bool operator == ( Grupo other )
    {
        return (F + T) == (other.F + other.T);
    }

};

inline void swap( Grupo& a, Grupo& b )
{
    Grupo temp = a;
    a = b;
    b = temp;
}
void descer(int i, Grupo array[],int n)
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

void makeHeap(Grupo array[],int n)
{
    for(int i = n/2 ; i>=1 ; i-- )
    {
        descer(i,array,n);
    }
}
void heapSort(Grupo array[],int size)
{
    makeHeap(array,size);

    for(int i=size; i > 1; i--)
    {
        descer(1,array,i);
        swap(array[1],array[i]);
    }
}


int N,M,K,P,F;
Elemento* vertex = NULL;
Elemento* repX = NULL;
Elemento* repY = NULL;
Grupo* grupo = NULL;
int gindex = 0;
int gsize = 0;
int A,B;
Grupo temp;
Grupo GLink,GZelda;
int nBattle = 0;

int getPred( Grupo grupo, Grupo array[] , int size)
{

    int i = 1;
    int melhor = i;

    for(i=1; i <= size; i++)
    {
        if( !array[i].vencido )
        {
            if( grupo >= array[i] )
            {
                if( array[i].F >= array[melhor].F )
                {
                    melhor = i;
                }
            }
            else break;
        }
    }

    i = melhor;

    /*
     int i = size;
    while(  grupo < array[i] || array[i].vencido  && i > 1)
    {
        i--;
    }

    */
    if( array[i].vencido || array[i] > grupo  ) i = -1;

    return i;
}

bool batalha()
{
    heapSort(grupo,gindex);

    int ipred = 0;
    bool ehpossivel = true;
    nBattle = 0;

    while( ehpossivel && (GLink.F + GLink.T) < (GZelda.F + GZelda.T - 1) || (GLink.F<GZelda.F && ! (( GLink.F + GLink.T) == (GZelda.F + GZelda.T - 1) ) ))
    {

        ipred = getPred(GLink,grupo,gindex);


        if(ipred>0 && grupo[ipred] <= GLink)
        {
            if( grupo[ipred] == GLink )
            {
                if( grupo[ipred].F <= GLink.F )
                {
                    GLink.F += grupo[ipred].F;
                    grupo[ipred].vencido = true;
                    nBattle++;
                }
            }
            else
            {
                GLink.F += grupo[ipred].F;
                grupo[ipred].vencido = true;
                nBattle++;

            }


        }
        else ehpossivel = false;

    }

    return GLink>=GZelda;

}


int main()
{
    freopen("L3QD.in","r",stdin);
    freopen("L3QD.out","w",stdout);

    int contConj = 0;

    while( scanf("%d %d", &N, &M) == 2)
    {
        vertex = new Elemento[N];


        gsize = N;

        for(int i=0; i < N; i++)
        {
            makeSet(vertex + i);
            vertex[i].added = false;
        }

        for(int i=0; i < M ; i++)
        {
            scanf("%d %d",&A,&B);


            repX = findSet(vertex + A);
            repY = findSet(vertex + B);

            if( repX != repY )
            {
                 sUnion(repX,repY);

                repX->tam += repY->tam;
                repY->tam = repX->tam;
               // gsize--;
            }
        }

        grupo = new Grupo[gsize + 1];
        gindex = 0;

        scanf("%d", &K);

        for(int i=0; i<K; i++)
        {
            scanf("%d %d",&P,&F);
            repX = findSet(vertex + P);

            if( F > repX->forcaDeus)
            {
                repX->forcaDeus = F;
            }
        }

        for(int i=0; i < N; i++)
        {
            repX = findSet(vertex + i);


            if( !repX->added && repX != (vertex + 1) && repX!=(vertex + 0))
            {
                temp.T = repX->tam;
                temp.F = repX->forcaDeus;
                temp.vencido = false;

                repX->added = true;

                if( (gindex + 1) <= gsize ) grupo[++gindex] = temp;
                else printf("ERRO NA ADICAO!!!");

            }
        }

        GLink.F = findSet(vertex + 0)->forcaDeus;
        GLink.T = findSet(vertex + 0)->tam;
        GZelda.F = findSet(vertex + 1)->forcaDeus;
        GZelda.T = findSet(vertex + 1)->tam;
        //printf("\nN %d M %d\n", N, M);
        //printf("Equipe #%d [Deus = %d , T = %d]",0,GLink.F,GLink.T);
        //printf("\nEquipe #%d [Deus = %d , T = %d]\n",1,GZelda.F,GZelda.T);




        batalha();

        printf("Conjunto #%d: ",++contConj);
        if( (GLink.F + GLink.T) >= (GZelda.F + GZelda.T - 1) )
        {
            printf( "POSSIVEL %d\n", nBattle + 1);

        }
        else printf( "IMPOSSIVEL\n");

         //getch();

        delete [] grupo;
        delete [] vertex;


    }



    return 0;
}
