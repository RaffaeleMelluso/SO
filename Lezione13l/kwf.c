#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    int kids, writes;
    if(argc < 4)
    {
        fprintf(stderr, "Not Enough Arguments");
        return -1;
    }
    if((fp=fopen(argv[1],"w"))==NULL)
    {
        fprintf(stderr, "Error opening file");
        return -1;
    }
    if(!(kids=atoi(argv[2])) || !(writes=atoi(argv[3])) || kids<0 || writes<0)
    {
        fprintf(stderr, "Argument Error");
        return -1;
    }
    for(int i=0;i<kids;i++)
    {
        if(!fork())
        {
            for(int j=0;j<writes;j++)
                fprintf(fp,"PID: %i\tPPID: %i\n",getpid(),getppid());
            exit(0);
        }
            
        
    }
    fclose(fp);
    return 0;




}
