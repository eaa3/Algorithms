#ifndef _STACK_
#define _STACK_

#include "SList.h"

template <class T>
class Stack : public SList<T>
{
    public:

        Stack();
        ~Stack();

        void push_front(T data);
        Node<T>* pop_front();

        Node<T>* getRoot();


};

template <class T>
Stack<T>::Stack() : SList<T>()
{

}
template <class T>
Stack<T>::~Stack()
{

}

template <class T>
void Stack<T>::push_front(T data)
{
    this->addRoot(data);
}

template <class T>
Node<T>* Stack<T>::pop_front()
{
    return this->removeRoot();
}

template <class T>
Node<T>* Stack<T>::getRoot()
{
    return this->root;
}

#endif
