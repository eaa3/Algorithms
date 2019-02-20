#include "heap.h"

Heap::Heap(int size)
{
    this->array = new int[size + 1];
    this->size = size + 1;
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
        this->array = new int[size + 1];
        this->size = size + 1;
        this->n = 0;
    }

}

void Heap::descer(int i)
{
    int esq = 2*i;
    int dir = 2*i + 1;
    int maior = esq;
    int temp;

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
    int temp;

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

bool Heap::inserir(int chave)
{
    if( (this->n + 1) < this->size )
    {
        this->array[++this->n] = chave;
        subir(this->n);

        return true;
    }

    return false;
}

bool Heap::remover(int *chave)
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
