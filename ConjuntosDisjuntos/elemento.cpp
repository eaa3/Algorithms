#include "elemento.h"



template <class T>
class Elemento<T>::Elemento()
{
    //this->rep = NULL;
    //this->rank = 0;
}

template <class T>
Elemento<T>::Elemento(T dado)
{
    this->dado = dado;
    this->rank = 0;
    this->rep = NULL;
}

