#include <stdio.h>
#include <string.h>

void data_column_process(int * data, int length, int * min, int * max, double * avg)
{
    double som=0;
    for(int i=0;i<length;i++)
    {
        if(data[i]>*max)
            *max=data[i];
        if(data[i]<*min)
            *min=data[i];
        som+=data[i];
    }
    *avg=som/(double)length;
}
int main (int argc, char * argv[])
{
    FILE *fp;
    char c;
    int i,j=1,x,col=1;
    int v[3];
    int min=99,max=0;
    double avg;
    if((fp=fopen("file.csv"/*argv[1]*/,"r"))==NULL)
        return -1;
    while(!feof(fp))
    {
        i=0;
        while ((c=fgetc(fp))!='\n')
        {
            x=1;
            while (c>='0' && c<='9')
            {
                
                for(int k=1;k<x;k++)
                    j*=10;
                v[i]+=(j)*(c-'0');
                c=fgetc(fp);
                
                i++;
                x++;
            }
            if(c=='\n')
                break;
              
        }
        data_column_process(v, i,&min,&max, &avg);
        printf("colonna %d, min=%d, max=%d, avg=%f\n",,min,max,avg);
        
    }
    fclose(fp);


}