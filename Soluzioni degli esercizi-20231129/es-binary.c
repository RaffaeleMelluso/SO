#include <stdio.h>
#include <stdlib.h>

#define VEC_LEN 256

/*
 * IDEA: fare la scansione dal bit piu` significativo al meno
 * significativo. In questo modo non serve riordinare i bit della
 * rappresentazione. Tale scansione di bit e` fatta con il bitwise AND
 * (&) fra il numero e una maschera opportuna che ha soltanto un bit
 * impostato a uno.
 */

int main ()
{
	char s[VEC_LEN];
	unsigned long n, i, mask;
#define NUM_BITS (sizeof(n)*8)
#define MOST_SIG_BIT1 ((unsigned long)1 << (NUM_BITS-1))

	/* Read string and convert into integer */
	printf("Enter the number to be converted\n");
	fgets(s, VEC_LEN, stdin);
	n = atol(s);
	
	printf("The binary representation of %lu is\n", n);
	if (n == 0) {
		printf("0\n");
		return 0;
	}

	/* 
	 * Cerca il bit piu` significativo impostato ad 1 di n. Questo
	 * e` fatto per evitare di stampare una lunga sequenza di "0"
	 * all'inizio della stringa. Siccome n != 0 alloca ci deve per
	 * forza essere almeno un bit a "1".
	 */
	for (mask = MOST_SIG_BIT1; !(mask & n);	mask >>= 1);

	/* 
	 * Scrivi i codici ASCII nella stringa a partire dal bit piu`
	 * significativo
	 */
	for(i=0; mask; mask >>= 1) {
		if (n & mask) {
			s[i++] = '1';
		} else {
			s[i++] = '0';
		}
	}

	/* Chiudi la stringa con 0 e stampala */
	s[i] = 0;
	printf("%s\n", s);
}
