#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *p,v[3],i;
    p=&v;
    *p=1;
    *(p+1)=2;
    for(i=0;i<3;i++)
    {
        printf("(%d) %d\n",i,*p);
        p++;
    }
    return 0;
}
