#include <stdio.h>

int main()
{
    int n,N,i=0;
    printf("Inserisci un numero N\n");
    scanf("%d",&N);
    while(N!=0)
    {
        n=N;
        while(n!=1)
        {
            i++;
            if(n%2==0)
                n=n/2;
            else
                n=3*n+1;
        }
        printf("%d\n",i);
        N--;
    }
    
    

    return 0;
}
