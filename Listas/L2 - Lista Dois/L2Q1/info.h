#ifndef INFO_H
#define INFO_H

#include "node.h"

class Info
{
    public:
        Info();
        Info(Node* address);
        virtual ~Info();

        Node* address;
        bool grew;

    protected:
    private:
};

#endif // INFO_H
