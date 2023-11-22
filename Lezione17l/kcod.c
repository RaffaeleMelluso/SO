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

int main(int argc, char *argv[])
{
    int nkids=atoi(argv[3]);
    int pid;
    char *status;
    if(nkids<0)
        fprintf(stderr,"Error in number of kids\n");
    for(int i=0;i<nkids;i++)
    {
        pid=fork();
        if(!pid)
        {
            if(execve("cl.out",argv, NULL)!=-1)
            {
                
            }
            else
                fprintf(stderr,"Errore nell'apertura di cl.c\n");
        }
        else
        {
            waitpid(pid,&status,0);
        }
    }
    
    
    return 0;
}
