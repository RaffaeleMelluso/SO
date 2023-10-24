#include <stdio.h>
#define MAX_LEN 5
#define MIN_AGE 1
#define MAX_AGE 10

typedef struct{
    char * name;
    int age;

} record;

record * rec_rand_create(int n){
    record * r = (record*) malloc(n*sizeof(record));
    int n1=(rand()+1)%MAX_LEN;
    for(int j=0;j<n;j++)
    {
        for(int i=0;i<n1;i++)
        {
        (r+j)->name=(rand()+33)%126;          //gen name
        r->name++;
        }
        r->name=(r->name)-n1;
        (r+j)->age=(rand()+MIN_AGE)%MAX_AGE;
        
    }
    
    
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
