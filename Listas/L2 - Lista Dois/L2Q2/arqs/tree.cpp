#include "tree.h"

Tree::Tree()
{
    this->nNodes = 0;
    this->root = NULL;
}

Tree::~Tree()
{
    this->clear();
}

Info Tree::add(Node* root,int key)
{
    Info infoOut;
    Info infoIn;

    if(!root)
    {
        infoOut.address = new Node(key);
        infoOut.grew = true;
        this->nNodes++;

    }
    else if(key > root->key)
    {
        infoIn = this->add(root->right,key);
        root->right = infoIn.address;

        if( infoIn.grew )
        {
            root->bal += 1;

            if((root->bal > 1) || (root->bal < -1))
            {
                if(root->bal>0 && root->right->bal>0)
                {
                    root = this->sRotLeft(root);
                }
                else if( root->bal>0 && root->right->bal<0 )
                {
                    root = this->dRotLeft(root);
                }
                infoOut.grew = false;
            }

            if(root->bal!=0) infoOut.grew = infoIn.grew;


        }

        infoOut.address = root;
    }
    else
    {
        infoIn = this->add(root->left,key);
        root->left = infoIn.address;

        if( infoIn.grew )
        {
            root->bal -= 1;

            if((root->bal > 1) || (root->bal < -1))
            {
                if(root->bal<0 && root->left->bal<0)
                {
                    root = this->sRotRight(root);
                }
                else if( root->bal<0 && root->left->bal>0 )
                {
                    root = this->dRotRight(root);
                }
                infoIn.grew = false;
            }

            if(root->bal!=0) infoOut.grew = infoIn.grew;


        }

        infoOut.address = root;

    }

    return infoOut;
}
void Tree::add(int key)
{
    Info infoIn = this->add(this->root,key);
    this->root = infoIn.address;

    /*if( infoIn.grew )
    {

        this->root->bal = this->getHeight(this->root->right) - this->getHeight(this->root->left);


        if((this->root->bal > 1) || (this->root->bal < -1))
        {
            if(this->root->bal > 0)
            {


                if(this->root->bal>0 && this->root->right->bal>0)
                {

                    this->root = this->sRotLeft(this->root);
                }
                else if( this->root->bal>0 && this->root->right->bal<0 )
                {

                    this->root = this->dRotLeft(this->root);
                }
            }
            else
            {


                if(this->root->bal<0 && this->root->left->bal<0)
                {
                    this->root = this->sRotRight(this->root);
                }
                else if( this->root->bal<0 && this->root->left->bal>0 )
                {

                    this->root = this->dRotRight(this->root);
                }
            }

        }
    }*/
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
}

int Tree::max(int a,int b)
{
    if( a >= b ) return a;
    else return b;
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

Node* Tree::getSuc(Node* root,Node** prev)
{
    Node* it = NULL;
    if(prev!=NULL) *prev = NULL;

    if(root)
    {
        if(prev!=NULL) *prev = root;
        it = root->right;

        if(it)
        {
            while(it->left)
            {
                if(prev!=NULL) *prev = it;
                it = it->left;
            }
        }

    }

    return it;
}
Node* Tree::search(Node* root,int chave)
{
    if(root)
    {

        if(chave > root->key)
        {
            return this->search(root->right,chave);
        }
        else if(chave < root->key)
        {
            return this->search(root->left,chave);
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

Node* Tree::search(int chave)
{
    return this->search(this->root,chave);
}

Node* Tree::remove(Node* root,int chave,bool *removeu)
{
    Node* retorno = root;

    if(root)
    {
        if(chave > root->key)
        {
            root->right = this->remove(root->right,chave,removeu);
        }

        else if(chave < root->key)
        {
            root->left = this->remove(root->left,chave,removeu);
        }

        else if(chave == root->key)
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

bool Tree::remove(int chave)
{
    bool removeu = false;

    this->root = this->remove(this->root,chave,&removeu);

    return removeu;
}

Node* Tree::sRotRight(Node* criticNode,bool aux)
{
    Node* newRoot = criticNode->left;

    criticNode->left = newRoot->right;
    newRoot->right = criticNode;


    criticNode->bal = 0;
    newRoot->bal = 0;
    cout << "Rotação simples para direita!" << endl;


    return newRoot;
}

Node* Tree::sRotLeft(Node* criticNode,bool aux)
{
    Node* newRoot = criticNode->right;

    criticNode->right = newRoot->left;
    newRoot->left = criticNode;

    criticNode->bal = 0;
    newRoot->bal = 0;
    cout << "Rotação simples para esquerda!" << endl;



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
    cout << "Rotação dupla para direita!" << endl;


    /*Node* newRoot = NULL;
    criticNode->left = sRotLeft(criticNode->left,true);

    newRoot = sRotRight(criticNode,true);


    criticNode->bal = 0;
    newRoot->bal = 0;

    cout << "Rotação dupla para direita!" << endl;*/

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

    cout << "Rotação dupla para esquerda!" << endl;



    /*
    Node* newRoot = NULL;
    criticNode->right = sRotRight(criticNode->right,true);

    newRoot = sRotLeft(criticNode,true);


    criticNode->bal = 0;
    newRoot->bal = 0;

    cout << "Rotação dupla para esquerda!" << endl;
    */

    return newRoot;
}


void Tree::printItPreOrdem(Node* root)
{
    if(!root) return;
    else
    {
        cout << root->key << endl;

        printItPreOrdem(root->left);
        printItPreOrdem(root->right);

    }
}

void Tree::printItPreOrdem()
{
    this->printItPreOrdem(this->root);

}
void Tree::printItOrdem(Node* root)
{
    if(root)
    {
        this->printItOrdem(root->left);

        cout << root->key << " ";

        this->printItOrdem(root->right);
    }
}

void Tree::printItOrdem()
{
    this->printItOrdem(this->root);
}

void Tree::printItPosOrdem(Node* root)
{
    if(root)
    {
        this->printItPosOrdem(root->left);
        this->printItPosOrdem(root->right);

        cout << root->key << endl;
    }
}
void Tree::printItPosOrdem()
{
    this->printItPosOrdem(this->root);
}
