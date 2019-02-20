#include <cstdio>
#include <cstring>
#include <math.h>
#include <iostream>

using namespace std;

#define MAX_STRING_SIZE 30
#define EQUAL 0

struct Packet
{
    char name[MAX_STRING_SIZE];

    int packetSize;

    //ArrivalTime on Router
    int arrivalTime;
    int processTime;

    int timeOut;

    bool lostPacket;

    bool operator < (Packet &other)
    {
        bool ret = arrivalTime < other.arrivalTime;

        if( !ret && arrivalTime == other.arrivalTime )
        {
            if(other.lostPacket)
            {
                ret = false;
            }
            else
            {
                ret = lostPacket;
            }
        }

        return ret;
    }
};

class Node
{
    public:
        Node();
        Node(Packet packet);
        ~Node();
        Node* next;
        Packet packet;
};

class List
{
    public:
        Node* root;
        Node* leaf;

        List();
        ~List();

        void addOrdered(Packet newPacket);
        void addBack(Packet newPacket);
        void remove(Packet packet);
        Packet popFront();

        void clear();
        bool hasNode();

        void remove(Node* previous,Node* current);

        int nNodes;

    protected:
        Node* addOrdered(Node* root, Packet &newPacket);

        Node* clear(Node* root);

};

class Router
{
    public:

        int bufferSize;
        int currentBufferSize;
        int speed;
        int currentNanoseconds;
        int lostPackets;

        void flowTime();



        Router();
        Router(int bufferSize,int speed);

        void addOrdered(Packet packet);
        bool hasSpace(Packet &packet);
        Packet getNextProcessed();

        List waitingQueue;

        List bufferQueue;

};

char bufStr[MAX_STRING_SIZE];
int nPackets = 0;
int tempos = 0;
int nanoseconds = 0;
Packet bufPacket;
int speed=0,size=0;
bool fimConjunto = false;
bool processing = true;
Node* iteratorCur = NULL;
Node* iteratorPre = NULL;
int count = 0;

Router router;

int main()
{
     freopen("L1Q1.in","r",stdin);

     freopen("L1Q1.out","w",stdout);

    while( scanf("%d %d",&speed,&size) == 2 )
    {
        printf("Conjunto #%d\n",++count);
        router = router(speed,size);
        do
        {
            scanf("%s",bufStr);
            fimConjunto = (strcmp(bufStr,"FIM") == EQUAL);

            if(!fimConjunto)
            {
                strcpy(bufPacket.name,bufStr);

                scanf("%d %d",&bufPacket.packetSize,&bufPacket.arrivalTime);

                bufPacket.timeOut = 0;
                bufPacket.processTime = 0;

                router.waitingQueue.addBack(bufPacket);



            }
        }while(!fimConjunto);

        nPackets = router.waitingQueue.nNodes;
        tempos = 0;

        do
        {

            while(router.waitingQueue.hasNode() && router.currentNanoseconds == router.waitingQueue.root->packet.arrivalTime)
            {
                    bufPacket = router.waitingQueue.popFront();

                    router.addOrdered(bufPacket);


                   // if(!router.waitingQueue.root) break;
            }



            if(router.bufferQueue.hasNode())
            {
                if(router.currentNanoseconds >= router.bufferQueue.root->packet.arrivalTime && !processing)
                {
                    processing = true;
                    router.bufferQueue.root->packet.timeOut = router.currentNanoseconds - router.bufferQueue.root->packet.arrivalTime  ;
                    //else router.bufferQueue.root->packet.timeOut = buf
                }

                else if( processing && router.currentNanoseconds >= (router.bufferQueue.root->packet.arrivalTime + router.bufferQueue.root->packet.processTime ) )
                {
                    bufPacket = router.getNextProcessed();
                    tempos += bufPacket.processTime;
                    printf("%d: %s foi processado em %dns e esperou %dns na fila\n",router.currentNanoseconds,bufPacket.name,bufPacket.processTime,bufPacket.timeOut);
                    processing = false;
                }

            }





        router.flowTime();
        }while( router.bufferQueue.hasNode() || router.waitingQueue.hasNode() );

        printf("%d %d media: %dns\n",nPackets,router.lostPackets,int(ceil(float(tempos)/nPackets)));




    }



    fclose(stdin);
    fclose(stdout);


    return 0;
}

Node::Node()
{
    this->next = NULL;

}
Node::Node(Packet packet)
{
    this->next = NULL;
    this->packet = packet;
}
Node::~Node()
{
}

List::List()
{
    this->root = NULL;
    this->leaf = NULL;
    this->nNodes = 0;
}
List::~List()
{
    this->clear();
}
Node* List::clear(Node* root)
{
    Node* temp = NULL;
    if(!root)
    {
        return NULL;
    }
    else
    {
        temp = this->clear(root->next);
        if(temp) delete temp;

        root->next = NULL;

        return root;
    }
}

void List::clear()
{
    Node* temp = this->clear(this->root);

    if(temp) delete temp;

    this->nNodes = 0;

    this->root = NULL;
}

Node* List::addOrdered(Node* root,Packet &newPacket)
{
    Node* ret = NULL;

    if(!root)
    {
        ret = new Node(newPacket);
        this->leaf = ret;
    }
    else if( newPacket < root->packet )
    {
            ret = new Node(newPacket);

            ret->next = root;
    }
    else
    {
        root->next = this->addOrdered(root->next,newPacket);

        ret = root;
    }


    return ret;
}

void List::addOrdered(Packet newPacket)
{

    this->root = this->addOrdered(this->root,newPacket);

    this->nNodes++;
}

void List::addBack(Packet newPacket)
{
    if(!this->root)
    {
        this->root = new Node(newPacket);
        this->leaf = this->root;
    }
    else
    {
        this->leaf->next = new Node(newPacket);
        this->leaf = this->leaf->next;
    }

    this->nNodes++;
}

Packet List::popFront()
{
    Node* temp = this->root;
    Packet packet;

    if(this->root)
    {
        packet = temp->packet;


        this->root = this->root->next;

        delete temp;

        this->nNodes--;

    }

    return packet;
}
bool List::hasNode()
{
    return (this->root != NULL);
}

void List::remove(Node* previous,Node* current)
{
    if(this->root == this->leaf && this->root == current)
    {
        this->root = NULL;
    }
    else if(current == this->leaf)
    {
        previous->next = NULL;
        this->leaf = previous;
    }
    else if(current == this->root)
    {
        this->root = current->next;
    }
    else if(previous)
    {
        previous->next = current->next;
        current->next = NULL;
    }

    delete current;

    current = NULL;
    if(this->nNodes>0) this->nNodes--;
}
Router::Router()
{
    this->speed = 0;
    this->bufferSize = 0;
    this->currentBufferSize = 0;
    this->currentNanoseconds = 0;
    this->lostPackets = 0;
}

Router::Router(int bufferSize,int speed)
{
    this->bufferSize = bufferSize;
    this->currentBufferSize = this->bufferSize;
    this->speed = speed;
    this->currentNanoseconds = 0;
    this->lostPackets = 0;
}

void Router::flowTime()
{
    this->currentNanoseconds++;
}

void Router::addOrdered(Packet packet)
{
    if( (this->currentBufferSize - packet.packetSize) >= 0)
    {
        this->currentBufferSize -= packet.packetSize;
        packet.processTime = int(ceil(float(packet.packetSize)/float(this->speed)));


        bufferQueue.addBack(packet);
    }
    else
    {
        packet.arrivalTime = packet.arrivalTime + int(ceil(float(packet.packetSize)/float(this->speed)));
        packet.lostPacket = true;
        packet.timeOut = 0;

        this->waitingQueue.addOrdered(packet);
        this->lostPackets++;

    }
}

Packet Router::getNextProcessed()
{
    Packet temp = this->bufferQueue.popFront();
    this->currentBufferSize += temp.packetSize;
    return temp;
}

