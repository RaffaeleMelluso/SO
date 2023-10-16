#include <stdio.h>
#include <stdlib.h>

void main(){
    char s[25];
    char *p1;
    int *p2;
    int v[25],n=0,i;

    p1=&s;
    p2=&v;
    printf("Inserisci una stringa\n");
    fgets(p1,sizeof(p1),stdin);
    printf("Stringa :\n %s \n",s);
    while (*p1!='\n')
    {
        *p2=(*p1-'0');
        p1++;
        p2++;
        n++;
    }
    for(i=0;i<n;i++)
    {
        printf("%i) [%i]\n",i,v[i]);
    }
    
    
}