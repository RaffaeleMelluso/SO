#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char * argv[])
{
    int nkids=atoi(argv[1]);
    int max=atoi(argv[2]);
    int num=atoi(argv[3]);
    int var=0;
    int kids[nkids];
    int a;
    for(int i=0;i<nkids;i++)
    {
        a=fork();
        if(a) //padre
        {
            kids[i]=a;
        } 
        else //figli
        {
            exit(0);    
        }
            
        
    }
    for(int i=0;i<nkids;i++)
    {
        printf("[%d]=%d\t",i,kids[i]);
    }
    
    
    return 0;
}