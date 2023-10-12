#include <stdio.h>

void main()
{
    unsigned int a,v[20],mask=1;
    int i;
    printf("Inserisci un intero senza segno\n");
    scanf("%d",&a);
    while (a>>1!=0)
    {
        v[i]=a&mask;
        
        a=a>>1;
        i++;
    
    }
    v[i]=a&mask;
    printf("La sua conversione in binario è\n[ ");
    while (i>=0)
    {
        printf("%d ",v[i]);
        i--;
    }
    printf("]\n");
    
    
}