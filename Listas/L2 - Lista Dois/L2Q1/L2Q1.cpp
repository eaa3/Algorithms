#include <cstdio>
#include <cstring>

#define MAXSTR 21

struct Contato
{
    char name[MAXSTR];
    int phone;

    bool operator > (Contato other)
    {
        return strcmp(name,other.name) > 0;
    }

    bool operator < (Contato other)
    {
        return strcmp(name,other.name) < 0;
    }

    bool operator == (Contato other)
    {
        return strcmp(name,other.name) == 0;
    }
};

struct InfoAdd
{
    bool addeu;
    int level;
};

class Node
{
public:
    Node();
    Node(Contato key);
    ~Node();

    Contato key;

    Node* left;
    Node* right;
};

class Tree
{
public:
    Tree();
    virtual ~Tree();

    Node* root;

    InfoAdd add(Contato key);
    bool remove(Contato key);


    int getHeight();

    void clear();

    Node* search(Contato key);



    int nNodes;

    //private:

    Node* add(Node* root, Contato key,InfoAdd *infoAdd = NULL);
    Node * clear(Node* root);
    int getHeight(Node* root);
    int max(int a,int b);
    int abs(int a);
    Node* getPre(Node* root,Node** prev = NULL);
    Node* remove(Node* root,Contato key,bool *removeu = NULL);
    Node* search(Node* root,Contato key);

};


Contato bufContato;
char bufCommand[MAXSTR];
InfoAdd infoAdd;
Node* resultSearch = NULL;
int bufQuaseK = 0;
bool fim = false;

Tree arvore;

int main()
{
    freopen("L2Q1.in","r",stdin);
    freopen("L2Q1.out","w",stdout);

    while ( scanf("%s",bufCommand) == 1 )
    {
        if( strcmp(bufCommand,"fim") != 0 )
        {
            scanf("%s",bufContato.name);

            if( strcmp(bufCommand,"inserir") == 0 )
            {
                scanf("%d",&bufContato.phone);

                infoAdd = arvore.add(bufContato);

                if(infoAdd.addeu)
                {
                    printf("%s inserido no nivel %d\n",bufContato.name,infoAdd.level);
                }
                else
                {
                    printf("%s ja existe no nivel %d\n",bufContato.name,infoAdd.level);

                }
            }

            else if(strcmp(bufCommand,"remover") == 0)
            {
                if( arvore.remove(bufContato) )
                {
                    printf("%s eliminado\n",bufContato.name);

                }
                else
                {
                    printf("contato inexistente\n");

                }
            }

            else if(strcmp(bufCommand,"buscar") == 0)
            {
                resultSearch = arvore.search(bufContato);

                if( resultSearch )
                {
                    printf("%s: %d\n",resultSearch->key.name,resultSearch->key.phone);
                }
                else
                {
                    printf("contato inexistente\n");
                }
            }

            else if( strcmp(bufCommand,"atualizar") == 0 )
            {
                scanf("%d",&bufContato.phone);

                resultSearch = arvore.search(bufContato);

                if( resultSearch )
                {
                    resultSearch->key.phone = bufContato.phone;
                    printf("%s: novo numero %d\n",resultSearch->key.name,resultSearch->key.phone);
                }
                else
                {
                    printf("contato inexistente\n");
                }
            }

            else if( strcmp(bufCommand,"quasi") == 0 )
            {
                resultSearch = arvore.search(bufContato);

                if( resultSearch )
                {
                    bufQuaseK = arvore.abs(arvore.getHeight(resultSearch->left) - arvore.getHeight(resultSearch->right));
                    printf("%s %d-quasiEquilibrado\n",resultSearch->key.name,bufQuaseK);
                }
                else
                {
                    printf("contato inexistente\n");
                }
            }




        }
        else
        {
            fim = true;
            printf("\n");
            arvore.clear();
        }

    }
    //while( !fim );

    fclose(stdout);
    fclose(stdin);



    return 0;
}

Node::Node()
{
    this->right = NULL;
    this->left = NULL;
}
Node::Node(Contato key)
{
    this->right = NULL;
    this->left = NULL;
    this->key = key;
}
Node::~Node()
{
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

Node* Tree::add(Node* root,Contato key,InfoAdd* infoAdd)
{
    Node* out;

    if(infoAdd != NULL) infoAdd->level++;

    if(!root)
    {
        out = new Node(key);
        this->nNodes++;

    }
    else if(key > root->key)
    {
        root->right = this->add(root->right,key,infoAdd);
        out = root;
    }
    else if(key < root->key)
    {
        root->left = this->add(root->left,key,infoAdd);
        out = root;

    }
    else
    {
        if(infoAdd != NULL)
        {
            infoAdd->addeu = false;
        }

        out = root;
    }

    return out;
}
InfoAdd Tree::add(Contato key)
{
    InfoAdd infoAdd= {true,-1};

    this->root = this->add(this->root,key,&infoAdd);

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

int Tree::max(int a,int b)
{
    if( a >= b ) return a;
    else return b;
}
int Tree::abs(int a)
{
    if( a < 0 ) return -a;
    else return a;
}
int Tree::getHeight(Node* root)
{
    int height = 0;

    if(!root)
    {
        return -1;
    }
    else
    {
        height = 1 + this->max(this->getHeight(root->left),this->getHeight(root->right));
    }

    return height;
}

int Tree::getHeight()
{
    int height = this->getHeight(this->root);
    return height;
}

Node* Tree::getPre(Node* root,Node** prev)
{
    Node* it = NULL;
    if(prev!=NULL) *prev = NULL;

    if(root)
    {
        if(prev!=NULL) *prev = root;
        it = root->left;

        if(it)
        {
            while(it->right)
            {
                if(prev!=NULL) *prev = it;
                it = it->right;
            }

        }
    }

    return it;
}
Node* Tree::search(Node* root,Contato key)
{
    if(root)
    {
        if(key > root->key)
        {
            return this->search(root->right,key);
        }
        else if(key < root->key)
        {
            return this->search(root->left,key);
        }
        else
        {
            return root;
        }
    }
    else
    {
        return NULL;
    }


}

Node* Tree::search(Contato key)
{
    return this->search(this->root,key);
}

Node* Tree::remove(Node* root,Contato key,bool *removeu)
{
    Node* retorno = root;

    if(root)
    {
        if(key > root->key)
        {
            root->right = this->remove(root->right,key,removeu);
        }

        else if(key < root->key)
        {
            root->left = this->remove(root->left,key,removeu);
        }

        else if(key == root->key)
        {
            if(removeu != NULL)
            {
                *removeu = true;
            }

            if( !root->left && !root->right )
            {
                retorno = NULL;
            }
            else if( root->left && root->right )
            {
                Node* fatherPre = NULL;
                retorno = this->getPre(root,&fatherPre);

                if(fatherPre != root)
                {

                    if(retorno->left)
                    {
                        fatherPre->right = retorno->left;
                        retorno->left = root->left;
                    }
                    else
                    {
                        fatherPre->right = NULL;
                        retorno->left = root->left;
                    }
                }

                retorno->right = root->right;

            }
            else if( root->left || root->right )
            {
                if(root->left)
                {
                    retorno = root->left;
                }
                else
                {
                    retorno = root->right;
                }
            }

            this->nNodes--;

            delete root;


        }

    }

    return retorno;

}

bool Tree::remove(Contato key)
{
    bool removeu = false;

    this->root = this->remove(this->root,key,&removeu);

    return removeu;
}



