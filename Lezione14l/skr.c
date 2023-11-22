#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#define NUM_KIDS 20

int main(int argc, char const *argv[])
{
    int num,status,sum=0,pid;
    for(int i=0;i<NUM_KIDS;i++)
    {
        pid=fork();
        if(!pid)
        {
            srand(getpid());
            num=(rand()+1)%7;
            printf("PID:%i\tN:%i\n",getpid(),num);
            exit(num);
        }
        else
        {
            while (wait(&status)!=-1)
            {
                sum+=WEXITSTATUS(status);
            }
            
        }
    }
    printf("Somma finale:%i\n",sum);
    return 0;
}
