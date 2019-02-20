#ifndef _QUEUE_
#define _QUEUE_

#include "SList.h"

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

#endif
