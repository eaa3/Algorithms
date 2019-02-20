#include <cstdio>
#include <cstring>

#define MAXSTR 21

struct InfoAdd
{
    bool addeu;
    bool rot;
    char tipoRot[MAXSTR];
};

struct Carro
{
    char modelo[MAXSTR];
    char placa[MAXSTR];


    bool operator > (Carro other)
    {
        return strcmp(placa,other.placa)>0;
    }
    bool operator < (Carro other)
    {
        return strcmp(placa,other.placa)<0;
    }
    bool operator == (Carro other)
    {
        return strcmp(placa,other.placa)==0;
    }

};

class Node
{
    public:
        Node();
        Node(Carro key);
        ~Node();

        Carro key;
        int bal;
        Node* left;
        Node* right;
};

struct InfoSearch
{
    bool found;
    int level;
    Node* node;
    int nModels;
};

class Info
{
    public:
        Info();
        Info(Node* address);
        Info(Node* address,bool grew);
        ~Info();

        Node* address;
        bool grew;
};
class Tree
{
    public:
        Tree();
        ~Tree();

        Node* root;

        InfoAdd add(Carro chave);
        bool remove(Carro chave);


        int getHeight();

        void clear();

        void printItPreOrdem();
        void printItOrdem();
        void printItPosOrdem();

        InfoSearch search(Carro chave);



        int nNodes;

    protected:

        Info add(Node* root, Carro chave,InfoAdd *infoAdd = NULL);
        Node * clear(Node* root);
        void printItPreOrdem(Node* root);
        void printItOrdem(Node* root);
        void printItPosOrdem(Node* root);
        Node* search(Node* root,Carro chave,InfoSearch* infoS = NULL);

        Node* sRotRight(Node* criticNode,bool aux = false);
        Node* sRotLeft(Node* criticNode,bool aux = false);

        Node* dRotRight(Node* criticNode);
        Node* dRotLeft(Node* criticNode);

};

Tree arvore;
char bufIn[MAXSTR];
InfoAdd infoAdd;
InfoSearch infoS;
Carro bufCarro;

int main()
{
    freopen("L2Q2.in","r",stdin);
    freopen("L2Q2.out","w",stdout);

    while(scanf("%s",bufIn) == 1)
    {
        while( strcmp(bufIn,"fim")!=0 )
        {
            if(strcmp(bufIn,"inserir") == 0)
            {
                scanf("%s %s",bufCarro.modelo,bufCarro.placa);

                infoAdd = arvore.add(bufCarro);

                if(infoAdd.addeu)
                {
                    printf("carro inserido com sucesso");
                    if(infoAdd.rot)
                    {
                        printf(" %s",infoAdd.tipoRot);
                    }
                    printf("\n");
                }
                else
                {
                    printf("carro ja cadastrado\n");
                }
            }
            else if(strcmp(bufIn,"buscar") == 0)
            {
                scanf("%s",bufCarro.placa);

                infoS = arvore.search(bufCarro);

                if(infoS.found)
                {
                    printf("%d: %d %s(s) neste ramo\n",infoS.level,infoS.nModels,infoS.node->key.modelo);
                }
                else
                {
                    printf("carro nao encontrado\n");
                }
            }
            else if(strcmp(bufIn,"imprimir")==0)
            {
                scanf("%s",bufIn);

                if(strcmp(bufIn,"in") == 0)
                {
                    arvore.printItOrdem();
                }
                else if(strcmp(bufIn,"pre") == 0)
                {
                    arvore.printItPreOrdem();
                }
                else if(strcmp(bufIn,"pos") == 0)
                {
                    arvore.printItPosOrdem();
                }


            }

            scanf("%s",bufIn);



        }

       arvore.clear();
       printf("\n");
    }


    fclose(stdout);
    fclose(stdin);

    return 0;
}

Node::Node()
{
   this->right = NULL;
   this->left = NULL;
   this->bal = 0;
}
Node::Node(Carro key)
{
    this->right = NULL;
    this->left = NULL;
    this->key = key;
    this->bal = 0;
}
Node::~Node()
{

}

Info::Info()
{
    this->address = NULL;
    this->grew = false;
}
Info::Info(Node* address)
{
    this->address = address;
    this->grew = false;
}
Info::Info(Node* address,bool grew)
{
    this->address = address;
    this->grew = grew;
}

Info::~Info()
{
    //dtor
}

Tree::Tree()
{
    this->nNodes = 0;
    this->root = NULL;
}

Tree::~Tree()
{
    this->clear();
}

Info Tree::add(Node* root,Carro key,InfoAdd* infoAdd)
{
    Info infoIn;
    Info infoOut;

    if(!root)
    {
        root = new Node(key);
        infoOut.grew = true;
        this->nNodes++;
    }
    else if(key > root->key)
    {
        infoIn = this->add(root->right,key,infoAdd);

        root->right = infoIn.address;

        if( infoIn.grew )
        {
            root->bal += 1;

            if(root->bal > 1)
            {
                if(root->right->bal>0)
                {
                    root = this->sRotLeft(root);
                    strcpy(infoAdd->tipoRot,"RSE");
                }
                else if(root->right->bal<0)
                {
                    root = this->dRotLeft(root);
                    strcpy(infoAdd->tipoRot,"RDE");
                }

                infoAdd->rot = true;

            }

            if(root->bal!=0){

                infoOut.grew = true;
            }
            else
            {
                infoOut.grew  = false;
            }
        }
        else
        {
            infoOut.grew = false;
        }

    }
    else if(key < root->key)
    {
        infoIn = this->add(root->left,key,infoAdd);
        root->left = infoIn.address;

        if( infoIn.grew )
        {
            root->bal -= 1;

            if(root->bal < -1)
            {
                if(root->left->bal<0)
                {
                    root = this->sRotRight(root);
                    strcpy(infoAdd->tipoRot,"RSD");
                }
                else if(root->left->bal>0)
                {
                    root = this->dRotRight(root);
                    strcpy(infoAdd->tipoRot,"RDD");
                }

                infoAdd->rot = true;

            }

            if(root->bal!=0)
            {
                infoOut.grew = true;
            }
            else
            {
                infoOut.grew = false;
            }
        }
        else
        {
            infoOut.grew = false;
        }

    }
    else
    {
        if(infoAdd!=NULL) infoAdd->addeu = false;
    }

    infoOut.address = root;

    return infoOut;
}
InfoAdd Tree::add(Carro key)
{
    InfoAdd infoAdd={true,false};
    Info infoIn = this->add(this->root,key,&infoAdd);
    this->root = infoIn.address;

    return infoAdd;
}
Node* Tree::clear(Node *root)
{
    Node* ret = NULL;

    if(root)
    {
        if(root->left) delete this->clear(root->left);
        if(root->right) delete this->clear(root->right);

        ret = root;
    }

    return ret;
}

void Tree::clear()
{
    delete this->clear(this->root);
    this->nNodes = 0;

    this->root = NULL;
}
Node* Tree::search(Node* root,Carro chave,InfoSearch* infoS)
{
    Node* returnNode = NULL;

    if(root)
    {
        if(infoS!=NULL) {
            infoS->level++;
        }


        if(chave > root->key)
        {
            returnNode = this->search(root->right,chave,infoS);
        }
        else if(chave < root->key)
        {
            returnNode = this->search(root->left,chave,infoS);
        }
        else
        {
            if(infoS!=NULL) infoS->found = true;
            returnNode =  root;
        }
    }

    if(returnNode && infoS)
    {
        if(strcmp(returnNode->key.modelo,root->key.modelo)==0) infoS->nModels++;
    }

    return returnNode;

}

InfoSearch Tree::search(Carro chave)
{
    InfoSearch infoS = {false,-1,NULL,0};
    infoS.node = this->search(this->root,chave,&infoS);

    return infoS;
}

Node* Tree::sRotRight(Node* criticNode,bool aux)
{
    Node* newRoot = criticNode->left;

    criticNode->left = newRoot->right;
    newRoot->right = criticNode;


    criticNode->bal = 0;
    newRoot->bal = 0;


    return newRoot;
}

Node* Tree::sRotLeft(Node* criticNode,bool aux)
{
    Node* newRoot = criticNode->right;

    criticNode->right = newRoot->left;
    newRoot->left = criticNode;

    criticNode->bal = 0;
    newRoot->bal = 0;

    return newRoot;
}

Node* Tree::dRotRight(Node* criticNode)
{

    Node* newRoot = criticNode->left->right;

    criticNode->left->right = newRoot->left;
    newRoot->left = criticNode->left;
    criticNode->left = newRoot->right;
    newRoot->right = criticNode;

    if(newRoot->bal>0)
    {
        criticNode->bal = 0;
        newRoot->left->bal = -1;

    }
    else if(newRoot->bal<0)
    {
        criticNode->bal = 1;
        newRoot->left->bal = 0;
    }
    else
    {
        criticNode->bal = 0;
        newRoot->left->bal = 0;
    }

    newRoot->bal = 0;


    return newRoot;
}

Node* Tree::dRotLeft(Node* criticNode)
{

    Node* newRoot = criticNode->right->left;

    criticNode->right->left = newRoot->right;
    newRoot->right = criticNode->right;
    criticNode->right = newRoot->left;
    newRoot->left = criticNode;

    if( newRoot->bal > 0 )
    {
        criticNode->bal = -1;
        newRoot->right->bal = 0;
    }
    else if(newRoot->bal<0)
    {
        criticNode->bal = 0;
        newRoot->right->bal = 1;

    }
    else
    {
        criticNode->bal = 0;
        newRoot->right->bal = 0;
    }

    newRoot->bal = 0;

    return newRoot;
}


void Tree::printItPreOrdem(Node* root)
{
    if(!root) return;
    else
    {
        printf("%s %s ",root->key.modelo,root->key.placa);

        printItPreOrdem(root->left);
        printItPreOrdem(root->right);

    }
}

void Tree::printItPreOrdem()
{
    this->printItPreOrdem(this->root);

    printf("\n");

}
void Tree::printItOrdem(Node* root)
{
    if(root)
    {
        this->printItOrdem(root->left);

        printf("%s %s ",root->key.modelo,root->key.placa);

        this->printItOrdem(root->right);
    }
}

void Tree::printItOrdem()
{
    this->printItOrdem(this->root);
    printf("\n");

}

void Tree::printItPosOrdem(Node* root)
{
    if(root)
    {
        this->printItPosOrdem(root->left);
        this->printItPosOrdem(root->right);

        printf("%s %s ",root->key.modelo,root->key.placa);
    }
}
void Tree::printItPosOrdem()
{
    this->printItPosOrdem(this->root);
    printf("\n");
}
