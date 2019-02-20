#include <cstdio>

//int next[] = {0, -1, 0, 0, 1, 2, 0, 1, 2, 3, 4, 3};

int* computeNext(char* pattern, int np)
{
    int *next = new int[np + 1];

    next[1] = -1;
    next[2] = 0;

    int j = 0;

    for(int i=3; i<=np;i++)
    {
        j = next[ i - 1 ] + 1;

        while( pattern[i - 2] != pattern[j - 1] && j>0) j = next[j] + 1;

        next[i] = j;
    }

    return next;
}

int stringMatching(char* text,int nt,char* pattern,int np)
{
    int i,j;
    i = j = 1;
    int start = -1;
    int* next = computeNext(pattern,np);

    for(int i=1;i<=np;i++) printf("%d ",next[i]);


    while( start == -1 && i<=nt )
    {
        if( pattern[j - 1] == text[i - 1] )
        {
            i++;
            j++;
        }
        else
        {
            j = next[j] + 1;

            if( j == 0 )
            {
                i++;
                j = 1;
            }
        }

        if( j > np ) start = (i - 1) - np;
    }

    delete [] next;

    return start;


}

int main()
{
    //char pattern[] = {'x','y','x','y','y','x','y','x','y','x','x','\0'};//11
    //char text[] = {'x','y','x','x','y','x','y','x','y','y','x','y','x','y','x','y','y','x','y','x','y','x','x','\0'};//23
    int np,nt;
    char pattern[10001];
    char text[10001];

    printf("Tamanho do padrao: ");
    scanf("%d",&np);
    printf("Tamanho do texto: ");
    scanf("%d",&nt);

    printf("Insira padrao: "); scanf("%s",pattern);
    printf("Insira texto: "); scanf("%s",text);


    int n = stringMatching(text,nt,pattern,np);

    printf("\n\nPrimeira ocorrencia encontrada na posicao: %d",n);

    return 0;


}
