#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
void handle_signal(int signal)
{
    printf("TIMEOUT\n");
    exit(-2);
}

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        fprintf(stderr, "Too few arguments\n");
        return -1;
    }
    if(argv[2]<0)
    {
        fprintf(stderr, "Too few iteration\n");
        return -1;
    }
    
    struct sigaction sa;
    sigset_t my_mask;
    bzero(&sa, sizeof(sa));
    sa.sa_handler=&handle_signal;

    if(sigaction(SIGALRM, &sa, NULL) == -1)
    {
        fprintf(stderr, "Failed setting handler\n");
    }

    int niter=atoi(argv[2]), 
        timeout=atoi(argv[1]);
    
    alarm(timeout);
    fprintf(stdout,"timeout argv[1]:%d, argv[2]:%d\n",timeout,niter);
    for(int i=1;i<=niter;i++)
    {
        printf("%i)I'm chilling\n",i);
        sleep(1);
    }
    exit(niter);
    return niter;
}
