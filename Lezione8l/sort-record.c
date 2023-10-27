#include <stdio.h>
#define MAX_LEN 3
#define MIN_AGE 1
#define MAX_AGE 10

typedef struct{
    char * name;
    int age;

} record;

record * rec_rand_create(int n){
    record * r = (record*) malloc(n*sizeof(record));
    record * ptr=&r;
    char * name=(char *) malloc(MAX_LEN*sizeof(char));
    char * pn=&name;
    int l;
    for(int i=0;i<n;i++)
    {
        ptr->age=(rand()+MIN_AGE)%MAX_AGE;
        l=(rand()+1)%MAX_LEN;
        for(int j=0;j<l;j++)
        {
            *pn=(rand()+65)%126;
            pn++;
        }
        ptr->name=&name;
        ptr++;
    }
    return r;
    
}

void rec_sort(record * v, int n)
{

}
void rec_print(record * v, int n){

}
void rec_free(record * v, int n){

}

void main(){
    int n=3;
    record * r= rec_rand_create(n);
    for(int i=0; i<n;i++)
    {
        printf("%s \t %i\n",r->name,r->age);
    }
}
