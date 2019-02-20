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
        int bal;
        Node* left;
        Node* right;

    protected:
    private:
};

#endif // NODE_H
