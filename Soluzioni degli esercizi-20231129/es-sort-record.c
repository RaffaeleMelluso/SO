#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10
#define AGE_MIN 10
#define AGE_MAX 100


typedef struct {
	char * name;
	int age;
} record;


record * rec_rand_create(int n)
{
	record * v;
	int i, j, len;
	
	if (n <= 0)
		return NULL;
	v = malloc(sizeof(*v)*n);
	for(i=0; i<n; i++) {
		len = rand() % MAX_LEN +1;
		v[i].name = malloc(len+1);
		for(j=0; j<len; j++) {
			v[i].name[j] = rand() % ('z'-'a'+1)+'a';
		}
		v[i].name[j] = 0;
		v[i].age = rand() % (AGE_MAX-AGE_MIN+1) + AGE_MIN;
	}
	return v;
}

void rec_sort(record * v, int n)
{
	record aux;
	int i, j, i_min;
	
	for(i=0; i<n-1; i++) {
		i_min = i;
		for(j=i; j<n; j++) {
			if (v[j].age < v[i_min].age)
				i_min = j;
		}
		if (i != i_min) {
			aux = v[i_min];
			v[i_min] = v[i];
			v[i] = aux;
		}
	}
}

void rec_print(record * v, int n)
{
	int i;

	for(i=0; i<n; i++) {
		printf("%s, %d\n", v[i].name, v[i].age);
	}
}

void rec_free(record * v, int n)
{
	int i;
	
	for(i=0; i<n; i++)
		free(v[i].name);
	free(v);
}

int main()
{
	int n;
	record * v;
	
	printf("Inserire numero di record\n");
	scanf("%i", &n);
	v = rec_rand_create(n);
	printf("ELENCO ORIGINALE\n");
	rec_print(v, n);
	rec_sort(v, n);
	printf("ELENCO ORDINATO\n");
	rec_print(v, n);
	rec_free(v,n);
}
