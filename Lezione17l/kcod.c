#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void handle_signal(int signal);

int main(int argc, char *argv[]) //argv[1] timeout, argv[2] niter, argv[3] nkids
{
    int nkids=atoi(argv[3]);
    int pid;
    char *status;
    if(nkids<0)
        fprintf(stderr,"Error in number of kids\n");
    for(int i=0;i<nkids;i++)
    {
        pid=fork();
        if(!pid) //figlio
        {
            if(execve("cl.out",argv, NULL)!=-1)
            {
                
            }
            else
                fprintf(stderr,"Errore nell'apertura di cl.c\n");
        }
        else //padre
        {
            while(wait(&status)!=-1)
            {
                if(WEXITSTATUS(status)==1)
                {
                    char new[4]=argv;
                    new[2]=(char*)(atoi(argv[2])/2);
                    pid=fork();
                    if(!pid)
                        execve("cl.out",new, NULL);
                }
            }
        }
    }
    
    
    return 0;
}
