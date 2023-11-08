#include <stdio.h>
#include <string.h>
#define size 50

int * cCR (char * stream)
{
    
    FILE *fp;
    char s[size];
    static int v[2]={1,1}; //colonne,righe
    static int err[2]={-1,-1};
    fp=fopen(stream,"r");
    if(fgets(s,size,fp)==NULL)
        return err;
    for(int i=0;i<size && s[i]!='\0';i++)
    {
        if(s[i]==',')
            v[0]++;
    }
    while (fgets(s,size,fp)!=NULL)
    {
        v[1]++;
    }
            
    fclose(fp);
    return v;
}
int main (int argc, char * argv[])
{
    FILE *fp;
    char s[size], *token;
    int min=99,max=0;
    int * cr=cCR("file.csv"/*argv[1]*/);
    double avg;
    if((fp=fopen("file.csv"/*argv[1]*/,"r"))==NULL)
        return -1;
    
    if((cr[0])==-1)
        return -1;
    
    int **m= (int**) malloc(cr[1] * sizeof(int*));
    for(int i=0;i<cr[1];i++)
        m[i]=(int*) malloc(cr[0]* sizeof(int));
    

    printf("rows:%i cols:%i\n",cr[1],cr[0]);
    for(int r=0;r<cr[1];r++)
    {
        fgets(s,size,fp);
        token=strtok(s,",");
        for(int c=0;token!=NULL;c++)
        {
            m[r][c]=strtol(token,NULL,10);
            printf("%d\t",m[r][c]);
            token=strtok(NULL,s);
        }
        printf("\n");
    }
    
    
    

        
    
    fclose(fp);


}