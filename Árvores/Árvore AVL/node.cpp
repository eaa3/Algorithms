#include "node.h"

Node::Node()
{
   this->right = NULL;
   this->left = NULL;
   this->key = 0;
   this->bal = 0;
}
Node::Node(int key)
{
    this->right = NULL;
    this->left = NULL;
    this->key = key;
    this->bal = 0;
}
Node::~Node()
{
   // cout << "fui destruido!" << endl;
}
