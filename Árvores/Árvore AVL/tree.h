#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "info.h"
#include <math.h>

class Tree
{
    public:
        Tree();
        virtual ~Tree();

        Node* root;

        void add(int chave);
        bool remove(int chave);


        int getHeight();

        void clear();

        void printItPreOrdem();
        void printItOrdem();
        void printItPosOrdem();

        Node* search(int chave);



        int nNodes;

    protected:

        Info add(Node* root, int chave);
        Node * clear(Node* root);
        int getHeight(Node* root);
        void printItPreOrdem(Node* root);
        void printItOrdem(Node* root);
        void printItPosOrdem(Node* root);
        int max(int a,int b);
        Node* getPre(Node* root,Node** prev = NULL);
        Node* getSuc(Node* root,Node** prev = NULL);
        Node* remove(Node* root,int chave,bool *removeu = NULL);
        Node* search(Node* root,int chave);

        Node* sRotRight(Node* criticNode,bool aux = false);
        Node* sRotLeft(Node* criticNode,bool aux = false);

        Node* dRotRight(Node* criticNode);
        Node* dRotLeft(Node* criticNode);

};

#endif // TREE_H
