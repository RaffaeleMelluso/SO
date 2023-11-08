/*
 * Segue lo svolgimento del seguente esercizio:
 *
 * Si scriva un  programma che legga una stringa da  stdin e, per ogni
 * carattere presente nella  stringa, scriva a stdout una  riga con il
 * numero di  occorrenze del  carattere nella  stringa e  il carattere
 * stesso.
 * 
 * IMPORTANTE:  Per  massimizzare  l'apprendimento, si  raccomanda  di
 * leggere  la  soluzione  proposta  soltanto *dopo*  aver  provato  a
 * risolvere il problema autonomamente.
 */
#include <stdio.h>

/* In questo modo e` possibile definire  STR_LEN sia a riga di comando
 * con
 *
 * gcc -D STR_LEN ...
 *
 * che usare un valore di default
 */
#ifndef STR_LEN
#define STR_LEN 20   /* default value */
#endif

/* number of ASCII characters */
#define ASCII_CHARS 256

int main()
{
	char s[STR_LEN];   /* stringa inserita */
	/* count[i] = numero di caratteri i  */
	unsigned int count[ASCII_CHARS], i;

	/* Leggi la stringa */
	printf("Inserire la stringa di cui contare i caratteri\n");
	fgets(s, STR_LEN, stdin);
	/* Inizializza il vettore con i contatoti di carattere */
	for(i=0; i<ASCII_CHARS; i++) {
		count[i] =  0;
	}
	/* Conta le occorrenze incrementando il contatore opportuno */
	for(i=0; i<STR_LEN; i++) {
		if (s[i] == 10) {
			/* Trovato a capo (cod ASCII 10), stringa finita */
			break;
		}
		/*
		 * il  cod ASCII  del  carattere corrente  s[i] e`  un
		 * numero e viene usato come indice in count
		 */
		count[s[i]]++;
		/* (*(count+s[i]))++; */
		/* (*(count+(*s+i)))++; */
	}
	if (i == STR_LEN) {
		/*
		 * Se la  stringa inserita  piu` lunga del  buffer, si
		 * suggerisce di raddoppiare il buffer.
		 */
		printf("Buffer insufficiente. Prova a ricompilare con:\n");
		printf("\n\t gcc -std=c89 -Wpedantic -D STR_LEN=%d %s\n\n", \
		       STR_LEN*2, __FILE__);
		return -1;
	}
	/* Stampa come richiesto */
	for(i=0; i<ASCII_CHARS; i++) {
		if (count[i]) {
			printf("%i,%c\n", count[i], i);
		}
	}
	return 0;
}
