#ifndef CONJUNTO_H
#define CONJUNTO_H

#include "elemento.h"

template <class T>
class Conjunto
{
public:

    Conjunto()
    {
    }

    ~Conjunto()
    {
    }


    void makeSet(Elemento<T>* x)
    {
        x->rep = x;
    }


    Elemento<T>* findSet(Elemento<T>* x)
    {
        //Representante
        Elemento<T>* rep = NULL;

        if( x->rep == x)
        {
            rep = x;
        }
        else
        {
            rep = findSet(x->rep);

            //Path Compression
            x->rep = rep;
        }

        return rep;
    }


    void link(Elemento<T>* x, Elemento<T>* y)
    {
        //Procura-se unir a árvore de menor rank à árvore de maior rank

        if( x->rank < y->rank )
        {
            x->rep = y;
        }
        else if(x->rank > y->rank)
        {
            y->rep = x->rep;
        }
        else
        {
            y->rep = x;

            x->rank++;
        }
    }


    void sUnion(Elemento<T>* x, Elemento<T>* y)
    {
        this->link( this->findSet(x) , this->findSet(y) );
    }

};

#endif // CONJUNTO_H
