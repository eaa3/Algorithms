#include <stdio.h>
#include <conio.h>

int main()
{
    freopen("L0Q2.in","r",stdin);
    freopen("L0Q2.out","w",stdout);

    int value = 0;
    int result = 0;
    int count = 0;
    char c ;

    int nLines = 0;

    scanf("%d\n",&nLines);

    while( !feof(stdin) || count<nLines)
    {
        scanf("%c",&c);

        if( c != '\n' && !feof(stdin) )
        {
            ungetc(c,stdin);
            //fseek(stdin,ftell(stdin) - 1,SEEK_SET);
            scanf("%d",&value);

            result += value;
        }
        else
        {
            printf("Resultado #%d: %d.\n",++count,result);
            result = 0;
        }
    }

    fclose(stdout);

    return 0;

}
