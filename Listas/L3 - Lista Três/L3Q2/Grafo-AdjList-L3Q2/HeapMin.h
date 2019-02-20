#ifndef _HEAPMIN_H
#define _HEAPMIN_H

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

#endif
