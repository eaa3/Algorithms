#include "info.h"

Info::Info()
{
    this->address = NULL;
    this->grew = false;
}
Info::Info(Node* address)
{
    this->address = address;
    this->grew = false;
}

Info::~Info()
{
    //dtor
}
