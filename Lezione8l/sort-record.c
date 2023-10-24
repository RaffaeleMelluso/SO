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
    record * ptr=r;
    int n1=(rand()+1)%MAX_LEN;
    for(int j=0;j<n;j++)
    {
        ptr->age=(rand()+1)%MAX_AGE;
        for(int i=0;i<n1;i++)
        {
            ptr->name[i]=(rand()+65)%126;
        }
        
        ptr++;
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
