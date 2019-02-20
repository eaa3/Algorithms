#ifndef _SLIST_
#define _SLIST_


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
    int size;

};
/*
template<class T>
void print(SList<T> &list)
{
    Node<T>* iterator = list.root;

    cout << endl;

    while(iterator)
    {
        cout << iterator->data << endl;
        iterator = iterator->next;

    }

}
*/
template <class T>
Node<T>::Node()
{
    this->next = NULL;
    this->cost = 1;

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
   // cout << "Fui destruido" << endl;

}

template<class T>
SList<T>::SList()
{
    this->root = NULL;
    this->leaf = NULL;
    this->size = 0;
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
    this->size = 0;
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

    this->size++;
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

    this->size++;

}

template<class T>
Node<T>* SList<T>::removeRoot()
{
    Node<T>* removedNode = this->root;

    if(this->root)
    {
        this->root = this->root->next;
        this->size--;

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
        this->size--;

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

                this->size--;
            }
            else
            {
                this->removeLeaf();
            }

        }

    }

    return removedNode;
}

#endif

