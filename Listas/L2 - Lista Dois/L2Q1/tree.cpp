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
	InfoAdd infoAdd={true,-1};

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
Node* Tree::search(Node* root,Contato key)
{
    if(root)
    {
        if(root->key == key)
        {
            return root;
        }
        else if(key > root->key)
        {
            return this->search(root->right,key);
        }
        else if(key < root->key)
        {
            return this->search(root->left,key);
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

/*
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
*/
