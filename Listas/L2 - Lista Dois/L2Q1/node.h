#ifndef NODE_H
#define NODE_H

#include <string>

using std::string;

struct Contato
{
	string name;
	int phone;

	bool operator > (Contato other)
	{
		return (name > other.name);
	}

	bool operator < (Contato other)
	{
		return (name < other.name);
	}

	bool operator == (Contato other)
	{
		return (name == other.name);
	}
};

class Node
{
    public:
        Node();
        Node(Contato key);
        virtual ~Node();

        Contato key;

        Node* left;
        Node* right;

    protected:
    private:
};

#endif // NODE_H
