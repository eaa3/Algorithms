#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <cstdlib>

template <class T>
class Elemento
{
public:

    Elemento()
    {
        this->rep = NULL;
        this->rank = 0;
    }


    Elemento(T dado)
    {
        this->dado = dado;
        this->rank = 0;
        this->rep = NULL;
    }


    int rank;
    T dado;
    Elemento<T>* rep;


};

#endif // ELEMENTO_H
