#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buf 100
int nrows(char * stream)
{
    FILE *fd;
    int row=0;
    char dummy[buf];
    fd=fopen(stream,"r");
    if(fd==NULL)
    {
        printf("Error");
        return -1;
    }
    while(fgets(dummy,buf,fd)!=NULL)
    {
        row++;
    }
    fclose(fd);
    return row;
}
int main(int argc, char const *argv[])
{
    FILE *fs, *fd;
    int r=nrows("fsorg.txt");
    int usciti[r];
    int num,j=0;
    char s[r][buf];

    if(r==-1)
    {
        printf("Error");
        return -1;   
    }
    if((fs=fopen(argv[1],"r"))==NULL || (fd=fopen(argv[2],"w"))==NULL)
    {
        printf("Error");
        return -1;
    }
    for(int i=0;fgets(s[i],buf,fs)!=NULL;i++);
    usciti[0]=rand()%(r);
    for(int i=1;i<r;i++)
    {
        num=rand()%(r);
        for(int j=0;j<=i;j++)
        {
            if(num==usciti[j])
                {
                    num=rand()%(r);
                    j=0;
                }
        }
        usciti[i]=num;
    }
    for(int i=0;i<r;i++)
    {
        printf("%i\n",usciti[i]);
    }
    for(int i=0;j<r;i++)
    {
        if(usciti[i]==j)
        {
            fputs(s[i],fd);
            j++;
            i=-1;
        }
    }

    
    
}
