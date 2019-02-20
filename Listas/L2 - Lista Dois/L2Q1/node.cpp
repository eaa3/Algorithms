#include "node.h"

Node::Node()
{
   this->right = NULL;
   this->left = NULL;
   //this->key = 0;
}
Node::Node(Contato key)
{
    this->right = NULL;
    this->left = NULL;
    this->key = key;
}
Node::~Node()
{
   // cout << "fui destruido!" << endl;
}
