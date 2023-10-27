#include <stdio.h>
#include <string.h>
#define MAX_LEN 7
#define MIN_AGE 1
#define MAX_AGE 100

typedef struct{
    char * name;
    int age;

} record;

record * rec_rand_create(int n){
    record * r = malloc(n*sizeof(*r));
    //record * ptr=r;
    char tmp_name[MAX_LEN+1];
    //char * pn=name;
    char alfabeto[]="abcdefghijKlmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int l_alfabeto=strlen(alfabeto);
    int l;
    for(int i=0;i<n;i++)
    {
        //ptr->age=(rand()+MIN_AGE)%MAX_AGE;
        r[i].age=(rand()+MIN_AGE)%MAX_AGE;
        l=(rand()%MAX_LEN)+1;
        for(int j=0;j<l;j++)
        {
            //*pn=alfabeto[rand()%l_alfabeto];
            //pn++;
            tmp_name[j]=alfabeto[rand()%l_alfabeto];
        }
        //ptr->name=strdup(name);
        //ptr++;
        tmp_name[l]='\0';
        r[i].name=strdup(tmp_name);
    }
    return r;
    
}

void rec_sort(record * v, int n)
{
    record tmp;
    int scambio;
    for(int j=0;j<n-1;j++)
    {
        scambio=0;
        for(int i=0;i<n-j-1 && scambio==0;i++)
        {
            if(v[i].age>v[i+1].age)
            {
                tmp=v[i];
                v[i]=v[i+1];
                v[i+1]=tmp;
                scambio=1;
            }
        }
    }

}
void rec_print(record * v, int n){
    for(int i=0; i<n;i++)
    {
        printf("%s \t %i\n",v[i].name,v[i].age);
    }
}
void rec_free(record * v, int n){
    free(v);
}

void main(){
    int n=3;
    record * r= rec_rand_create(n);
    rec_print(r,n);

    printf("\nOrdino il record:\n");
    rec_sort(r,n);
    rec_print(r,n);
    free(r);

}
