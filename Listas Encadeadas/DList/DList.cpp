#include <iostream>
#include <exception>

using std::endl;
using std::cout;
using std::cin;
using std::exception;

class NotFoundNodeException : exception
{
    public:

    NotFoundNodeException();

    const char* what() const throw();
};

template <class T>
class Node
{
    public:
        T data;
        Node* next;
        Node* previous;

        Node(T data);
        Node();
        virtual ~Node();

};

template <class T>
class DList
{
    public:

        Node<T>* root;
        Node<T>* leaf;

        DList();
        ~DList();

        void addRoot(T data);
        void addLeaf(T data);

        T removeRoot();
        T removeLeaf();
        T remove(T data) throw(NotFoundNodeException);

};

template<class T>
void print(DList<T> &list);

int main()
{

    DList<int> lista;

    int a=15,b=20,c=10,d=33;

    lista.addLeaf(b);
    lista.addLeaf(a);
    lista.addRoot(c);
    lista.addRoot(d);



    print(lista);

    //lista.removeRoot();
    //lista.removeLeaf();
    //lista.removeLeaf();
    lista.remove(33);

    cout << endl;

    /*Node<int>* iterator = lista.leaf;

    while(iterator)
    {
        cout << iterator->data << endl;
        iterator = iterator->previous;
    }

    cout << endl;
    */

    //lista.remove(b);

    //cout << "No removido: " << *lista.removeLeaf() << endl;

   /* try
    {
        lista.remove(0);

    }
    catch(NotFoundNodeException erro)
    {
        cout << erro.what() << endl;
    }*/


    print(lista);

    cin.get();

    return 0;
}

NotFoundNodeException::NotFoundNodeException()
{

}

const char* NotFoundNodeException::what() const throw()
{
    return "There aren't a node with that information!";
}

template<class T>
void print(DList<T> &list)
{
    Node<T>* iterator = list.root;

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
    this->previous = NULL;

}

template<class T>
Node<T>::Node(T data)
{
    this->next = NULL;
    this->previous = NULL;

    this->data = data;
}

template<class T>
Node<T>::~Node()
{
    cout << "Fui destruido" << endl;

}

template<class T>
DList<T>::DList()
{
    this->root = NULL;
    this->leaf = NULL;
}

template<class T>
DList<T>::~DList()
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
void DList<T>::addRoot(T data)
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
        this->root->previous = newNode;
        this->root = newNode;
    }
}

template<class T>
void DList<T>::addLeaf(T data)
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
        newNode->previous = this->leaf;
        this->leaf = newNode;
    }

}

template<class T>
T DList<T>::removeRoot()
{
    Node<T>* removedNode = this->root;
    T removedData;

    if(this->root)
    {
        this->root = this->root->next;

        removedData = removedNode->data;

        if(this->root == this->leaf)
        {
            this->root = NULL;
            this->leaf = NULL;
        }
        else
        {
            this->root->previous = NULL;
        }

        delete removedNode;


    }

    return removedData;
}

template <class T>
T DList<T>::removeLeaf()
{
    Node<T>* removedNode = this->leaf;
    T removedData;

    if(this->leaf)
    {
        if(this->root == this->leaf)
        {
            this->root = NULL;
            this->leaf = NULL;
        }
        else
        {
            this->leaf->previous->next = NULL;
            this->leaf = this->leaf->previous;
        }

        removedData = removedNode->data;

        delete removedNode;

    }

    return removedData;

}
template <class T>
T DList<T>::remove(T data) throw(NotFoundNodeException)
{
    T removedData;

    if(this->root)
    {
        if(this->root->data == data)
        {
            removedData = this->root->data;
            this->removeRoot();
        }
        else if( this->leaf->data == data )
        {
            removedData = this->leaf->data;
            this->removeLeaf();
        }
        else
        {
            //Sentinela
            this->addLeaf(data);

            Node<T>* current = this->root;
            //Node<T>* previous = NULL;

            while( current->data != data )
            {
                current = current->next;
            }

            if(!current->next)
            {
                this->removeLeaf();

                throw NotFoundNodeException();

            }

            this->removeLeaf();

            removedData = current->data;

            current->previous->next = current->next;
            current->next->previous = current->previous;

            delete current;

        }

    }
    else
    {
        throw NotFoundNodeException();
    }

    return removedData;
}



