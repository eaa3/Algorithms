#include <cstdio>
#include <cstring>

const int MAXSTRLEN = 31;
const int EQUAL = 0;
const int RIGHT = 0;
const int LEFT = 1;

char bufStr[MAXSTRLEN];
int bufInt = 0;


class Music
{
public:
    Music();
    Music(char* name,int execTime = 0);

    char name[MAXSTRLEN];
    int execTime,repeatCount;

    bool operator==(Music &other);


};

class Node
{
public:

    Node();
    Node(Music music);
    ~Node();

    Music music;

    Node* next;
    Node* prev;
};

//Lista Circular
class PlayList
{
public:
    Node* root;
    Node* leaf;

    int nNodes;

    PlayList();
    ~PlayList();

    bool addBack(Music music);
    bool remove(Music music);
    bool remove(Node* it);
    Node* search(Music music,int &count);
    Node* search(Music music);

    void clear();

};

class Player
{
public:
    PlayList playList;
    Node* cursor;
    int sentido,elapsedTime;

    Player();

    void moveFoward(int x);
    void moveBackward(int x);
    void moveCursor(int x);
    void moveCursor();
    void play();
    void search(Music music);

    void addMusic(Music music);
    void removeMusic(Music music);

    void printEndOfSet();

    void reinit();
};

bool flagInitSetOK = false;

int main()
{
    freopen("L1QD3.in","r",stdin);
    freopen("L1QD.out","w",stdout);
    int countSet = 0;
    Player player;
    Music bufMusic;

    while(scanf("%s",bufStr) != EOF )
    {

        if( strcmp(bufStr,"inicio") == EQUAL)
        {
            if(countSet>0)
            {
                player.printEndOfSet();
                printf("\n");
            }

            countSet++;
            printf("Conjunto #%d\n",countSet);
            player.playList.clear();
            player.cursor = NULL;
            flagInitSetOK = true;
            player.elapsedTime = 0;
            player.sentido = RIGHT;
        }

        else
        {
            if( strcmp(bufStr,"inserir") == EQUAL )
            {

                scanf("%s %d",bufMusic.name,&bufMusic.execTime);

                player.addMusic(bufMusic);

            }
            else if( strcmp(bufStr,"remover") == EQUAL )
            {
                scanf("%s",bufStr);
                strcpy(bufMusic.name,bufStr);

                player.removeMusic(bufMusic);
            }
            else if ( strcmp(bufStr,"avancar") == EQUAL )
            {
                scanf("%d",&bufInt);
                player.moveFoward(bufInt);
            }
            else if( strcmp(bufStr,"voltar") == EQUAL )
            {
                scanf("%d",&bufInt);
                player.moveBackward(bufInt);
            }
            else if( strcmp(bufStr,"buscar") == EQUAL )
            {
                scanf("%s",bufStr);
                strcpy(bufMusic.name,bufStr);
                player.search(bufMusic);
            }
            else if( strcmp(bufStr,"tocar") == EQUAL )
            {
                player.play();
            }


        }


    }
    player.printEndOfSet();
    printf("\n");

    fclose(stdin);
    fclose(stdout);

    return 0;
}

Music::Music()
{
    this->execTime = 0;
    this->repeatCount = 0;
}
Music::Music(char* name, int execTime)
{
    strcpy(this->name,name);
    this->execTime = execTime;
    this->repeatCount = 0;
}

bool Music::operator==(Music &other)
{
    return (strcmp(this->name,other.name) == EQUAL);
}

Node::Node()
{
    this->next = NULL;
    this->prev = NULL;
}
Node::Node(Music music)
{
    this->music = music;
    this->next = NULL;
    this->prev = NULL;
}
Node::~Node()
{
}

PlayList::PlayList()
{
    this->root = NULL;
    this->leaf = NULL;
    this->nNodes = 0;
}
PlayList::~PlayList()
{
    this->clear();
}

bool PlayList::addBack(Music music)
{
    bool alreadyExists = (this->search(music) != NULL);

    if(!alreadyExists)
    {
        if(!this->root)
        {
            this->root = new Node(music);
            this->leaf = this->root;

            this->root->next = this->leaf;
            this->root->prev = this->leaf;

            this->leaf->next = this->root;
            this->leaf->prev = this->root;
        }
        else
        {
            Node* newNode = new Node(music);

            this->leaf->next = newNode;
            newNode->prev = this->leaf;
            newNode->next = this->root;
            this->leaf = newNode;
            this->root->prev = this->leaf;
        }

        this->nNodes++;
    }

    return !alreadyExists;
}

Node* PlayList::search(Music music)
{
    bool found = false;

    Node* initOffset = this->root;
    Node* it = initOffset;

    if(this->root)
    {
        do
        {
            found = (it->music == music);

            if(!found) it = it->next;

        }
        while(!found && it != initOffset);
    }

    if(found) return it;
    else return NULL;
}

bool PlayList::remove(Music music)
{
    Node* it = this->search(music);

    return this->remove(it);
}
bool PlayList::remove(Node* it)
{
    bool found = (it != NULL);

    if(found)
    {

        if(this->root == this->leaf)
        {
            this->root = NULL;
            this->leaf = NULL;
        }
        else
        {
            if( it == this->root )
            {
                this->root = this->root->next;
                this->root->prev = this->leaf;
                this->leaf->next = this->root;
            }
            else if(it == this->leaf)
            {
                this->leaf = this->leaf->prev;
                this->leaf->next = this->root;
                this->root->prev = this->leaf;
            }
            else
            {
                it->next->prev = it->prev;
                it->prev->next = it->next;
            }



        }

        this->nNodes--;

        delete it;
    }

    return found;

}
Node* PlayList::search(Music music,int &count)
{
    bool found = false;

    Node* initOffset = this->root;
    Node* it = initOffset;

    count = 0;

    do
    {
        found = (it->music == music);

        if(!found)
        {
            it = it->next;
            count++;
        }

    }
    while(!found && it != initOffset);

    if(found) return it;
    else return NULL;
}


void PlayList::clear()
{
    Node* initOffset = this->root;
    Node* current = initOffset;
    Node* previous = NULL;

    if(this->root)
    {

        do
        {
            previous = current;
            current = current->next;

            delete previous;

        }
        while( current != initOffset );
    }

    this->root = NULL;
    this->leaf= NULL;
    this->nNodes = 0;
}

Player::Player()
{
    this->reinit();
}

void Player::reinit()
{
    this->elapsedTime = 0;
    this->sentido = RIGHT;
    this->cursor = NULL;

}

void Player::moveFoward(int x)
{
    this->sentido = RIGHT;

    if(this->cursor)
    {
        this->moveCursor(x);
    }
}

void Player::moveBackward(int x)
{

    this->sentido = LEFT;

    if( this->cursor )
    {
        this->moveCursor(x);
    }
}

void Player::moveCursor(int x)
{
    if(this->cursor)
    {
        if(sentido == RIGHT)
        {
            for(int i=0; i < x; i++)
            {
                this->cursor = this->cursor->next;
            }
        }
        else
        {
            for(int i=0; i < x; i++)
            {
                this->cursor = this->cursor->prev;
            }
        }
    }

}
void Player::moveCursor()
{
    if(this->cursor)
    {
        if(sentido == RIGHT)
        {

            this->cursor = this->cursor->next;

        }
        else
        {
            this->cursor = this->cursor->prev;
        }
    }
}


void Player::addMusic(Music music)
{
    music.repeatCount = 0;

    bool firstInsert = ( this->cursor==NULL || this->playList.root == NULL );

    bool hasInserted = this->playList.addBack(music);

    if(firstInsert && hasInserted)
    {
        this->cursor = this->playList.root;

        if(flagInitSetOK)
        {
            this->elapsedTime = 0;
            flagInitSetOK = false;
        }
    }

    if(hasInserted)
    {
        printf("%s inserida\n",music.name);
    }
    else
    {
        printf("%s ja existe\n",music.name);
    }
}

void Player::removeMusic(Music music)
{

    Node* it = this->playList.search(music);
    bool found = (it != NULL);

    if(found && this->cursor)
    {
        printf("%s removida\n",it->music.name);

        if(this->cursor == it)
        {
            if(this->cursor == this->playList.root && this->playList.root == this->playList.leaf)
            {
                this->cursor = NULL;

            }
            else
            {
                this->moveCursor();
            }

        }

        this->playList.remove(it);

    }
    else
    {
        printf("musica inexistente\n");
    }




}

void Player::play()
{
    if(this->cursor)
    {
        printf("%d: %s\n",this->elapsedTime,this->cursor->music.name);

        this->elapsedTime += cursor->music.execTime;
        this->cursor->music.repeatCount++;

        this->moveCursor();
    }
}

void Player::search(Music music)
{
    int count = 0;
    bool found = false;

    if(this->playList.root && this->cursor)
    {
        Node* initOffset = this->cursor;

        do
        {
            found = this->cursor->music == music;

            if(!found)
            {
                this->moveCursor();
                count++;
            }

        }
        while(this->cursor != initOffset && !found);
    }


    if(!found )
    {
        printf("%s inexistente\n",music.name);

    }
    else
    {
        printf("%d: %s %d\n",count,cursor->music.name,cursor->music.execTime);

        this->play();
    }
}
void Player::printEndOfSet()
{
    printf("%d\n",this->elapsedTime);

    if(this->cursor)
    {

        Node* initOffset = this->cursor;

        do
        {
            printf("%d: %s\n",this->cursor->music.repeatCount,this->cursor->music.name);

            this->moveCursor();
        }
        while(this->cursor != initOffset);
    }

}









