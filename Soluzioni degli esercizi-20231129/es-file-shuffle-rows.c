#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/* Utile macro per stampa errori */
#define PRINT_ERROR fprintf(stderr,					\
			    "%s:%d: Errore %d \"%s\"\n",		\
			    __FILE__, __LINE__, errno, strerror(errno));


/* Dimensione iniziale della memoria allocata per una riga */
#define ROW_SIZE_INIT 4


int main(int argc, char * argv[]) {
	FILE * in_f, * out_f;
	int c;
	char ** rows_array; /* NULL-terminated array of pointers to rows */
	size_t rows_array_size, rows_array_i, i, i_pick;
	char * row_cur, *aux;
	size_t row_cur_size, row_cur_i;
	
	/* 
	 * Il primo  argomento letto a  riga di comando argv[1]  e` il
	 * nome del file da cui leggere
	 */
	if ((in_f = fopen(argv[1], "r")) == NULL) {
		PRINT_ERROR;
		exit(EXIT_FAILURE);
	}

	/* 
	 * Il secondo argomento letto a  riga di comando argv[2] e` il
	 * nome del file su cui scrivere
	 */
	if ((out_f = fopen(argv[2], "w")) == NULL) {
		PRINT_ERROR;
		exit(EXIT_FAILURE);
	}

	/* Inizializza l'array per contenere solo un elemento che varra` NULL */
	rows_array_size = 1;
	rows_array = malloc(rows_array_size*sizeof(*rows_array));
 	rows_array_i = 0;

	/* Inizializza memoria per una riga */
	row_cur_size = ROW_SIZE_INIT;
	row_cur = calloc(row_cur_size, 1);
	row_cur_i = 0;
	
	/* Ciclo di lettura file e caricamento in memoria */
	while ((c = getc(in_f)) != EOF) {
		if (c == 10) { /* new line */
			/* Chiudi riga corrente */
			row_cur[row_cur_i] = 0;
			/* Controlla se array di puntatori deve crescere */
			if (rows_array_i >= rows_array_size) {
				rows_array_size <<= 1; /* raddoppia */
				rows_array = realloc(rows_array, rows_array_size*sizeof(*rows_array));
			}
			/* Memorizza puntatore a riga */
			rows_array[rows_array_i] = row_cur;
			rows_array_i++;
			/* Alloca per nuova riga */
			row_cur_size = ROW_SIZE_INIT;
			row_cur = calloc(row_cur_size, 1);
			row_cur_i = 0;
		} else { /* normal character */
			/* Controlla se riga deve crescere */
			if (row_cur_i >= row_cur_size-1) {
				row_cur_size <<= 1;
				row_cur = realloc(row_cur, row_cur_size);
			}
			/* Memorizza carattere */
			row_cur[row_cur_i] = c;
			row_cur_i++;
		}
	}  /* end while loop */

	if (row_cur_i == 0) {
		/* Riga corrente e` vuota, va deallocata */
		free(row_cur);
	} else {
		/* Riga corrente e` piena, va memorizzata */
		row_cur[row_cur_i] = 0;
		/* Controlla se array di puntatori deve crescere */
		if (rows_array_i >= rows_array_size) {
			rows_array_size <<= 1; /* raddoppia */
			rows_array = realloc(rows_array, rows_array_size*sizeof(*rows_array));
		}
		/* Memorizza puntatore a riga */
		rows_array[rows_array_i] = row_cur;
		rows_array_i++;
	}
	fclose(in_f);

	/* Rimescola le righe scambiando i puntatori */
	srand(time(NULL));  /* inizializza random seed */
	for (i=rows_array_i-1; i>0; i--) {
		/*  indice riga da scambiare con la i */
		i_pick = rand() % (i+1);
		if (i_pick != i) {
			/* exchange rows */
			aux = rows_array[i];
			rows_array[i] = rows_array[i_pick];
			rows_array[i_pick] = aux;
		}
	}

	/* Scrivi file tdi output */
	for (i=0; i<rows_array_i; i++) {
		fprintf(out_f, "%s\n", rows_array[i]);
	}

	/* Chiudi file e libera memoria */
	fclose(out_f);
	for (i=0; i<rows_array_i; i++) {
		free(rows_array[i]);
	}
	free(rows_array);
}
