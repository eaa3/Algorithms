#include <cstdio>
#include <conio.h>
//int next[] = {0, -1, 0, 0, 1, 2, 0, 1, 2, 3, 4, 3};
int next[10001];

int* computeNext(char* pattern, int np)
{
    //int *next = new int[np + 1];

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
    int end = -1;
    int count = 0;
    computeNext(pattern,np);

    //for(int i=1;i<=np;i++) printf("%d ",next[i]);
    //printf("\n");


    while(  i <= nt )
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

        if( j == (np + 1) )
        {
            count++;
            start = (i - 1) - np;
            end = start + (np - 1);
            printf("%d %d\n",start,end);

            //if(i<=nt)
            //{
                j = next[j - 1] + 1;


                if( j == 0 ){
                    j = 1;
                    i++;
                }
                //printf("\n Jota = %d\n",j);
                //getch();

            //}



        }

        //if( i >= nt ) break;
    }

    //delete [] next;

    return count;


}

int main()
{
    //char pattern[] = {'x','y','x','y','y','x','y','x','y','x','x','\0'};//11
    //char text[] = {'x','y','x','x','y','x','y','x','y','y','x','y','x','y','x','y','y','x','y','x','y','x','x','\0'};//23

    freopen("L4Q1.in","r",stdin);
    freopen("L4Q1.out","w",stdout);
    int np,nt,nk,nc;
    char pattern[10001];
    char text[10001];

    while( scanf("%d",&nk) == 1)
    {
        for(int i=0;i<nk;i++)
        {
            scanf("%d %d",&np,&nt);
            scanf("%s",pattern);
            scanf("%s",text);
            nc = stringMatching(text,nt,pattern,np);
            printf("%d\n\n",nc);
        }
    }


    fclose(stdout);

    return 0;


}

