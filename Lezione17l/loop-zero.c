#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int n_kids, var=0;
pid_t * children; 

void handler(int signum)
{
    

}
int main(int argc, char * argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Utilizzo: %s <nkids> <max> <num>\n", argv[0]);
        return 1;
    }

    int nkids = atoi(argv[1]);
    int max = atoi(argv[2]);
    int num = atoi(argv[3]);
    int kids[nkids];
    int a;


    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = &handler;


    

    for(int i=0;i<nkids;i++)
    {
        a=fork();
        if(a) //padre
        {
            
            kids[i]=a;
            if(i==nkids-1)
            {
                for(int var=0;var<=max;var++)
                {
                    

                    if(var==max)
                    {
                        var=-1;
                    }
                    
                }
            }
        } 
        else //figli
        {
            for(int var=0;var<=max;var++)
            {
                if(var==max)
                {
                    var=-1;
                    kill(getppid(),SIGUSR1);
                }
            }
            exit(0);    
        }
            
        
    }
    for(int i=0;i<nkids;i++)
    {
        printf("[%d]=%d\t",i,kids[i]);
    }
    
    
    return 0;
}