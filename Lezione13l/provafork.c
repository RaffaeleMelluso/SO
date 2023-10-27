#include <stdio.h>
#include <unistd.h>

void main()
{
    
    int a=fork();
    if(a)
        printf("%d\n",a);
    else
        printf("%d\n",fork());
}