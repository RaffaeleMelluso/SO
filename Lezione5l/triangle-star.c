#include <stdio.h>

int main(int argc, char const *argv[])
{
    int b,h,i,j;
    printf("Inserisci l'altezza intera\n");
    scanf("%d",&b);
    printf("Inserisci la base intera\n");
    scanf("%d",&h);
    for(i=h;i>=0;i--)
    {
        for(j=0;j<b-i;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
