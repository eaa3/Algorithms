#include <iostream>

using std::endl;
using std::cout;
using std::cin;

template <class T>
class Node
{
public:
    T data;
    Node* next;

    Node(T data);
    Node();
    ~Node();

};

template <class T>
class SList
{
public:

    Node<T>* root;
    Node<T>* leaf;

    SList();
    ~SList();

    void addRoot(T data);
    void addLeaf(T data);

    Node<T>* removeRoot();
    Node<T>* removeLeaf();
    Node<T>* remove(T data);

};

template <class T>
class Queue : private SList<T>
{
    public:

        Queue();
        ~Queue();

        void push_back(T data);
        Node<T>* pop_front();

        Node<T>* getRoot();


};

template<class T>
void print(SList<T> &list);
template<class T>
void printStack(Queue<T> &queue);

int main()
{
    Queue<int> queue;

    queue.push_back(10);
    queue.push_back(20);
    queue.push_back(30);

    printStack(queue);
    Node<int>* rmv = queue.pop_front();
    cout <<"\nOia-> " << rmv->data << endl;
    delete rmv;

    rmv = queue.pop_front();
    cout <<"\nOia-> " << rmv->data << endl;
    delete rmv;

    rmv = queue.pop_front();
    cout <<"\nOia-> " << rmv->data << endl;
    delete rmv;

    printStack(queue);


    cin.get();

    return 0;
}

template<class T>
void print(SList<T> &list)
{
    Node<T>* iterator = list.getRoot();

    cout << endl;

    while(iterator)
    {
        cout << iterator->data << endl;
        iterator = iterator->next;

    }

}
template<class T>
void printStack(Queue<T> &queue)
{
    Node<T>* iterator = queue.getRoot();

    cout << endl;

    while(iterator)
    {
        cout << iterator->data << endl;
        iterator = iterator->next;

    }

}

template <class T>
Node<T>::Node()
{
    this->next = NULL;

}

template<class T>
Node<T>::Node(T data)
{
    this->next = NULL;

    this->data = data;
}

template<class T>
Node<T>::~Node()
{
    cout << "Fui destruido" << endl;

}

template<class T>
SList<T>::SList()
{
    this->root = NULL;
    this->leaf = NULL;
}

template<class T>
SList<T>::~SList()
{
    Node<T>* current = this->root;
    Node<T>* previous = NULL;

    while(current)
    {
        previous = current;

        current = current->next;

        delete previous;
    }
}

template<class T>
void SList<T>::addRoot(T data)
{
    Node<T>* newNode = new Node<T>(data);

    if(!this->root)
    {
        this->root = newNode;
        this->leaf = newNode;
    }
    else
    {
        newNode->next = this->root;
        this->root = newNode;
    }
}

template<class T>
void SList<T>::addLeaf(T data)
{
    Node<T>* newNode = new Node<T>(data);

    if(!this->root)
    {
        this->root = newNode;
        this->leaf = newNode;
    }
    else
    {
        this->leaf->next = newNode;
        this->leaf = newNode;
    }

}

template<class T>
Node<T>* SList<T>::removeRoot()
{
    Node<T>* removedNode = this->root;

    if(this->root)
    {
        this->root = this->root->next;

    }

    return removedNode;
}

template <class T>
Node<T>* SList<T>::removeLeaf()
{
    Node<T>* removedNode = this->leaf;

    if(this->leaf)
    {
        Node<T>* iterator = this->root;

        if(this->leaf == this->root)
        {
            this->root = NULL;
            this->leaf = NULL;
        }
        else
        {
            while(iterator->next != this->leaf)
            {
                iterator = iterator->next;
            }

            iterator->next = NULL;
            this->leaf = iterator;

        }

    }

    return removedNode;

}
template <class T>
Node<T>* SList<T>::remove(T data)
{
    Node<T>* removedNode = NULL;

    if(this->root)
    {
        if(this->root->data == data)
        {
            this->root->data;
            removedNode = this->removeRoot();
        }
        else
        {
            //Sentinela
            this->addLeaf(data);

            Node<T>* current = this->root;
            Node<T>* previous = NULL;

            while( current->data != data )
            {
                previous = current;

                current = current->next;
            }

            if(current->next)
            {
                this->removeLeaf();

                removedNode = current;

                previous->next = current->next;
            }
            else
            {
                this->removeLeaf();
            }

        }

    }

    return removedNode;
}
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

template <typename T>
Node<T>* Queue<T>::getRoot()
{
    return this->root;
}


