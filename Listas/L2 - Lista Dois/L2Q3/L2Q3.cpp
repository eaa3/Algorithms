#include <cstdio>
#include <cstring>

#define MAXSTR 21

struct Tarefa
{
    char nome[MAXSTR];
    int tempo;
    //senha de chegada
    int senha;

    bool operator > (Tarefa& other)
    {
        if( tempo == other.tempo )
        {
            return senha < other.senha;
        }

        return tempo > other.tempo;
    }
    bool operator < (Tarefa& other)
    {
        if( tempo == other.tempo )
        {
            return senha > other.senha;
        }

        return tempo < other.tempo;
    }
};

class Heap
{
public:

    Tarefa *array;
    int n;
    int size;

    void constroi();
    void descer(int i);
    void subir(int i);
    bool inserir(Tarefa chave);
    bool remover(Tarefa *chave);

    int getSize();

    void clear();
    void init(int size);

    Heap(int size);
    Heap();
    ~Heap();

};

int A=0,N=0,currentTime=0;
Tarefa bufTarefa;
char bufIn[MAXSTR];
bool fim = false;

inline void realizarTarefa(Heap& heap)
{
    heap.remover(&bufTarefa);

    if( bufTarefa.tempo > A )
    {
        currentTime+=A;
        bufTarefa.tempo-=A;
        printf("%d: %s feita. %d minutos gastos. %d minutos restantes.\n",currentTime,bufTarefa.nome,A,bufTarefa.tempo);
        heap.inserir(bufTarefa);
    }
    else
    {
        currentTime+=bufTarefa.tempo;
        printf("%d: %s feita. %d minutos gastos. Tarefa completa.\n",currentTime,bufTarefa.nome,bufTarefa.tempo);
    }


}


int main()
{
    freopen("L2Q3.in","r",stdin);
    freopen("L2Q3.out","w",stdout);

    int countSenha = 0;
    Heap heap;


    while( scanf("%d %d",&N,&A)==2 )
    {

        heap.init(N);
        currentTime = 0;
        fim = false;

        while( !fim  )
        {
            scanf("%s",bufIn);

            fim = (strcmp(bufIn,"fim") == 0 );

            if(!fim)
            {
                if((strcmp(bufIn,"adicionar") == 0))
                {
                    scanf("%s %d",bufTarefa.nome,&bufTarefa.tempo);

                    bufTarefa.senha = countSenha++;

                    heap.inserir(bufTarefa);
                    printf("%d: %s adicionada.\n",currentTime,bufTarefa.nome);

                }

                if((strcmp(bufIn,"fazer") == 0))
                {
                    scanf("%s",bufIn);


                    if(strcmp(bufIn,"tarefa") == 0)
                    {
                        if(heap.n>0) realizarTarefa(heap);
                    }
                }

            }



        }

        while( heap.n > 0 )
        {
            realizarTarefa(heap);
        }
        printf("\n");
        heap.clear();

    }



    fclose(stdout);
    fclose(stdin);

    return 0;
}

Heap::Heap(int size)
{
    this->array = new Tarefa[size + 1];
    this->size = size + 1;
    this->n = 0;
}
Heap::Heap()
{
    this->array = NULL;
    this->size = 0;
    this->n = 0;
}

Heap::~Heap()
{
    this->clear();
}

void Heap::clear()
{
    delete [] this->array;
    this->array = NULL;
}

void Heap::init(int size)
{
    if(!this->array)
    {
        this->array = new Tarefa[size + 1];
        this->size = size + 1;
        this->n = 0;
    }

}

void Heap::descer(int i)
{
    int esq = 2*i;
    int dir = 2*i + 1;
    int maior = esq;
    Tarefa temp;

    //Se ele ao menos tiver um filho à esquerda
    if( esq <= this->n )
    {
        //Se ele tiver um filho à direita tbm...
        if( esq < this->n )
        {
            if( this->array[dir] > this->array[esq] )
            {
                maior = dir;
            }
        }

        if( this->array[i] < this->array[maior] )
        {
            temp = this->array[i];
            this->array[i] = this->array[maior];
            this->array[maior] = temp;

            this->descer(maior);
        }
    }
}

void Heap::subir(int i)
{
    int pai = i/2;
    Tarefa temp;

    //Se o nó de índice i tiver pai...
    if( pai >= 1)
    {
        if( this->array[i] > this->array[pai] )
        {
            temp = this->array[pai];

            this->array[pai] = this->array[i];
            this->array[i] = temp;

            this->subir(pai);
        }
    }
}

void Heap::constroi()
{
    for(int i = this->n/2 ; i>=1 ; i-- )
    {
        this->descer(i);
    }
}

bool Heap::inserir(Tarefa chave)
{
    if( (this->n + 1) < this->size )
    {
        this->array[++this->n] = chave;
        subir(this->n);

        return true;
    }

    return false;
}

bool Heap::remover(Tarefa *chave)
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

int Heap::getSize()
{
    return this->size - 1;
}

