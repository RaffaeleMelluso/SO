    #include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX_LEN 13
#define MIN_AGE 5
#define MAX_AGE 95

typedef struct {
    char * name ;
    int age ;
} record;


record * rec_rand_create(int n); // prototipo funzione creazione
void rec_sort ( record * v , int n ) ;
void rec_print ( record * v , int n ) ;
void rec_free ( record * v , int n ) ;

int main(){

    srand(time(NULL));
    int dimensione;
    record * v_rec;


    do{
        printf("Inserire la dimensione del vettore che si vuole creare\n");
        scanf("%d",&dimensione);
    }while(dimensione <= 0);

    v_rec =rec_rand_create(dimensione);

   printf("Ecco gli elementi inseriti all'interno del vettore\n");
   rec_print (v_rec,dimensione);

    printf("\n\n\nEcco gli elementi del vettore ordinati per età crescente\n");
    rec_sort (v_rec , dimensione );
    rec_print (v_rec,dimensione);
    rec_free ( v_rec,dimensione);
}

record * rec_rand_create(int n){ // corpo della funzione prototipo
    // alloco array di record di dimensione n;
    record * vet_rec =  malloc(sizeof(*vet_rec)*n);
     // allocato il vettore;
    char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int lunghezza = strlen(alfabeto),stringa_randomica,car_sc;
    for(int i = 0; i!=n;i++){

        vet_rec[i].age = MIN_AGE + rand() % (MAX_AGE - MIN_AGE +1);
        // lunghezza stringa randomica
        stringa_randomica = (1+rand() % (MAX_LEN));

        char nomeP[stringa_randomica];

        for(int j = 0;j!=stringa_randomica;j++){
            car_sc = rand() % lunghezza;
            nomeP[j] = alfabeto[car_sc];
        }
        nomeP[stringa_randomica] = '\0';
        (vet_rec[i].name = strdup(nomeP)) ;

    }
    return vet_rec;
}

void rec_sort ( record * v , int n ){
    int scambiaE = 0;

    for(int i = 0;i<(n-1);i++){
        for(int j = i+1;j!= n;j++){
            if(v[i].age>=v[j].age){
                scambiaE = v[i].age;
                char *stringa =v[i].name;
                v[i].age = v[j].age;
                v[i].name = strdup(v[j].name);
                v[j].age = scambiaE;
                v[j].name = strdup(stringa);
            }

        }
    }
}

void rec_print ( record * v , int n ){
    for(int i = 0;i!= n;i++)
        printf("%s\t\t%d anni\n",v[i].name,v[i].age);
}

void rec_free ( record * v , int n ){
    for(int i = 0; i!=n;i++){
        free(v[i].name);
    }
    free(v);
}

// quando si ha un puntatore all'interno della struct, bisogna allocare dinamicamete dello spazio in memoria, anche per quegli attributi e poi
//una volta utilizzati bisogna liberare lo spazio occupato attraverso una free;