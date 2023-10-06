#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v[7],i;
    char s[25], *ptr;
    for(i=0;i<7;i++)
    {
        printf("Inserisci un numero\n");
        v[i]=strtol(fgets(s,sizeof(s),stdin), &ptr, 10);
    }
       
    for(i=1;i<7;i+=2)
        printf("[%d] %d\n",i,v[i]);
    for(i=0;i<7;i+=2)
        printf("[%d] %d\n",i,v[i]);
    return 0;
}