#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node
{
    public:
        Node();
        Node(int key);
        virtual ~Node();

        int key;

        Node* left;
        Node* right;

    protected:
    private:
};

#endif // NODE_H
