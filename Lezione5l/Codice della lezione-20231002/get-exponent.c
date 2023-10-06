#include <stdio.h>
#include <math.h>
int main()
{
    float f;
    int cont=0;
    printf("Inserisci un numero decimale senza segno\n");
    scanf("%f",&f);
    while(f!=(int)f)
    {
        f=f*2;
        cont--;
    }
    while (f>=2)
    {
        f=(int)f>>1;
        cont++;
    }
    cont+=127;
    printf("L'esponente e' %d\n",cont);
    
    return 0;
}