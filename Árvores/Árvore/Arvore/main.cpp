#include "tree.h"
#include "vetor2D.h"

void printTree(Tree &tree);
Vetor2D dir[] = { Vetor2D(1,1)*2 , Vetor2D(-1,1)*2 };



int main()
{
    Tree arvore;

    int n = 0;

    while( n >= 0)
    {
        cin >> n;
        if(n>=0) arvore.add(n);

    }
    arvore.printItPreOrdem();



    /*
    int array[] = { 20, 25, 22, 21, 24, 23, 40, 27, 26, 50, 45, 10, 15, 5, 6, 7, 8};

    for(int i=0;i<17;i++)
    {
        cout << array[i] << " ";
        arvore.add(array[i]);
    }
    cout << endl;
    cout << "\nnNodes-> " << arvore.nNodes << endl;
    for(int i=0;i<arvore.nNodes;i++)
    {
        cout << "Altura(" << array[i] << ")-> " << arvore.getHeight(arvore.search(array[i])) << endl;
    }
    cout << endl;

    //arvore.remove(arvore.root,10);
    cout << "\nnNodes-> " << arvore.nNodes << endl;
    arvore.printItOrdem();


    Node* temp;
    Node* pred;
    for(int i=0;i<arvore.nNodes;i++)
    {
        pred = arvore.getPre(arvore.search(array[i]),&temp);
        cout << "Pred(" << array[i] << ")-> ";
        if(pred) cout << pred->key;
        else cout << pred;
        cout << endl;
        cin.get();
    }


    //cout <<"Pre->" <<  arvore.getPre(arvore.search(10))->key << endl;


    arvore.remove(20);

    cout << "\n nNodes-> " << arvore.nNodes << endl;
    arvore.printItOrdem();
    */


    return 0;
}
void drawNode(int *array,int w,int h,Vetor2D posAt,Node* root)
{
    //cout << posAt.toString() << endl;


    if(root)
    {
        //cout << root->key << endl;
        array[int(posAt.getY())*w + int(posAt.getX())] = root->key;

        if(root->right)
        {
            drawNode(array,w,h,posAt + dir[0],root->right);
        }

        if(root->left)
        {
            drawNode(array,w,h,posAt + dir[1] + Vetor2D(-1,0),root->left);
        }
    }

}
void printTree(Tree& tree)
{
    int h = tree.getHeight()*int(dir[0].proj(Vetor2D(0,1)).getNorma());
    int w = (dir[0]*h).proj(Vetor2D(1,0)).getNorma()*2 + 1;

    h++;

    int* array = new int[h*w];
    Vetor2D posAt(w/2,0);

    cout << h << "x" << w << endl;
    for(int i=0;i<h*w;i++) array[i] = -99999;

    drawNode(array,w,h,posAt,tree.root);

    for(int i=0; i < h ; i++)
    {
        for(int j=0; j < w ; j++)
        {
            if(array[i*w + j] == -99999) cout << "   ";
            else cout << array[i*w + j];
        }
        cout << endl;
    }

    delete [] array;



}


