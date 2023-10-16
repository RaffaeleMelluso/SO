#include <stdio.h>
#include <stdlib.h>

void main(){
    char s[25];
    char *p, *ptr;
    p=&s;
    printf("Inserisci una stringa\n");
    fgets(p,sizeof(p),stdin);
    printf("Stringa :\n %s \n",s);
    int a,b,i;
    printf("Inserisci a\n");
    a=strtol(fgets(&a,sizeof(a),stdin), &ptr, 10);
    printf("Inserisci b\n");
    b=strtol(fgets(&b,sizeof(b),stdin), &ptr, 10);
    while(*p!=s[a])
        p++;
    i=a;
    while(i<b && (*p>='0' && *p<='9'))
    {
        i++;
        p++;
    }
    if(i==b)
        printf("Si\n");
    else
        printf("No\n");
    
        



}