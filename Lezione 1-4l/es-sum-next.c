#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v1[10],v2[10],i,j;
    char s[25],*ptr;

    for(i=0;i<10;i++)
    {
        printf("Inserisci un numero\n");
        v1[i]=strtol(fgets(s,sizeof(s),stdin), &ptr, 10);
    }
    for(i=0;i<10;i++)
        v2[i]=v1[i];
    
    printf("Valori inseriti\n");
    for(i=0;i<10;i++)
        printf("[%d] %d\n",i,v1[i]);
    for(i=0;i<10;i++)
    {
        for(j=i+1;j<10;j++)
            v2[i]+=v1[j];
    }
    printf("Vettore somma\n");
    for(i=0;i<10;i++)
        printf("[%d] %d\n",i,v2[i]);

    return 0;
}