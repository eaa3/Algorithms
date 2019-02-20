#ifndef HEAP_H
#define HEAP_H

class Heap
{
    public:

        int *array;
        int n;
        int size;

        void constroi();
        void descer(int i);
        void subir(int i);
        bool inserir(int chave);
        bool remover(int *chave);

        int getSize();

        void clear();
        void init(int size);

        Heap(int size);
        ~Heap();

};

#endif // HEAP_H
