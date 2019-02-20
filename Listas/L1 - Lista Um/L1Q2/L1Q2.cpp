#include <fstream>
#include <string>

using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;


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

        void clear();

        T removeRoot();
        T removeLeaf();
        T remove(T data);

};

template<class T>
class DStack
{
    private:
        DList<T> list;
    public:
        DStack();
        ~DStack();

        void push_back(T data);
        T pop_back();

        bool hasNode();

        void clear();
};

template<class T>
void print(DStack<T> &stack);

ifstream in("L1Q2.in");
ofstream out("L1Q2.out");
DStack<string> previousPageStack;
DStack<string> nextPageStack;
string buffer,currentURL;
int count = 0;

bool ignorado = false;

int main()
{

    currentURL = "http://www";

    out << "Conjunto #" << ++count << endl;

    while( in >> buffer )
    {

        if(buffer == "visitar")
        {
            previousPageStack.push_back(currentURL);
            nextPageStack.clear();
            in >> currentURL;

        }
        else if (buffer == "voltar")
        {
            ignorado = !previousPageStack.hasNode();

            if(!ignorado)
            {
                nextPageStack.push_back(currentURL);
                currentURL = previousPageStack.pop_back();
            }
        }
        else if ( buffer == "seguir" )
        {
            ignorado = !nextPageStack.hasNode();

            if(!ignorado)
            {
                previousPageStack.push_back(currentURL);
                currentURL = nextPageStack.pop_back();
            }

        }



        if(buffer == "sair")
        {
            if(!in.eof()) out << "\nConjunto #" << ++count << endl;
            previousPageStack.clear();
            nextPageStack.clear();
            currentURL = "http://www";
        }
        else
        {
            if(ignorado)
            {
                out << "ignorado" << endl;
                ignorado = false;
            }
            else
            {
                out << currentURL << endl;
            }
        }



    }
    out << endl;

    out.close();
    in.close();

    return 0;
}

template <class T>
void print(DStack<T> &stack)
{
    Node<T>* iterator = stack.leaf;
    while(iterator)
    {

        out << iterator->data << endl;
        iterator = iterator->previous;
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
    this->clear();
}
template<class T>
void DList<T>::clear()
{
    Node<T>* current = this->root;
    Node<T>* previous = NULL;

    while(current)
    {
        previous = current;

        current = current->next;

        delete previous;
    }

    this->root = NULL;
    this->leaf = NULL;
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
T DList<T>::remove(T data)
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



            }

            this->removeLeaf();

            removedData = current->data;

            current->previous->next = current->next;
            current->next->previous = current->previous;

            delete current;

        }

    }


    return removedData;
}

template <class T>
DStack<T>::DStack()
{

}
template <class T>
DStack<T>::~DStack()
{

}
template <class T>
void DStack<T>::push_back(T data)
{
    this->list.addLeaf(data);
}
template <class T>
T DStack<T>::pop_back()
{
    return this->list.removeLeaf();
}

template <class T>
bool DStack<T>::hasNode()
{
    return this->list.leaf != NULL;
}
template<class T>
void DStack<T>::clear()
{
    this->list.clear();
}




