#include <stdio.h>
#include <stdlib.h>

int * fibo(int n)
{
    int *v= (int*)malloc(n*sizeof(int));
    int i,som=0;
    v[0]=0;
    v[1]=1;
    for(i=2;i<n;i++)
    {
        v[i]=v[i-1]+v[i-2];
    }
    return v;

}
void main()
{
    int n,i;
    printf("Inserisci n\n",n);
    scanf("%d",&n);
    int *v = fibo(n);
    for(i=0;i<n;i++)
    {
        printf("%d) %d\n",i,v[i]);
    }
    free(v);

}