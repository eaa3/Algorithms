#ifndef TREE_H
#define TREE_H

#include "node.h"

struct InfoAdd
{
	bool addeu;
	int level;
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

        //void printItPreOrdem();
        //void printItOrdem();
        //void printItPosOrdem();

        Node* search(Contato key);



        int nNodes;
		
    //protected:

		Node* add(Node* root, Contato key,InfoAdd *infoAdd = NULL);
        Node * clear(Node* root);
        int getHeight(Node* root);
        //void printItPreOrdem(Node* root);
        //void printItOrdem(Node* root);
        //void printItPosOrdem(Node* root);
        int max(int a,int b);
        int abs(int a);
        Node* getPre(Node* root,Node** prev = NULL);
        Node* getSuc(Node* root,Node** prev = NULL);
        Node* remove(Node* root,Contato key,bool *removeu = NULL);
        Node* search(Node* root,Contato key);

};

#endif // TREE_H
