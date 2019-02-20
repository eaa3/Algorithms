#include "node.h"

Node::Node()
{
   this->right = NULL;
   this->left = NULL;
   this->key = 0;
}
Node::Node(int key)
{
    this->right = NULL;
    this->left = NULL;
    this->key = key;
}
Node::~Node()
{
   // cout << "fui destruido!" << endl;
}
