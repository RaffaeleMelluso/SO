#include <stdio.h>
#include <stdlib.h>

void main(){
    
    char s[25];
    char *p1,*ptr;
    int *p2;
    int v[25],n=0,i,a=0,b,c,j;

    p1=&s;
    p2=&v;
    printf("Inserisci una stringa\n");
    fgets(p1,sizeof(p1),stdin);
    printf("Inserisci b\n");
    b=strtol(fgets(&b,sizeof(b),stdin), &ptr, 10);
    if(b>=2 && b<=32)
    {
        while (*p1!='\n')
        {
            *p2=(*p1-'0');
            p1++;
            p2++;
            n++;
        }
        p2=&v;
        for(i=0;i<n;i++)
        {
            printf("%i) [%i]\n",i,v[i]);
        }
        for(i=0;i<n;i++)
        {
            c=1;
            for(j=0;j<i;j++)
                c*=b;
            a+=*p2*c;
            p2++;
        }
        printf("Il numero in intero e' %d\n",a);
    }
    else
        printf("Base sbagliata");
    

    
}