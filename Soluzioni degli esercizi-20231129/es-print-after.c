/*
 * Si scriva  un programma che legge  due stringhe di caratteri  (s1 e
 * s2) di lunghezza massima di 80 caratteri mediante fgets.
 *
 * Preliminarmente, il programma  chiude entrambe le stringhe  s1 e s2
 * scrivendo  il byte  0  sul primo  byte non  stampabile  (un byte  è
 * stampabile se ha codice ASCII compreso fra 32 e 126). (questo serve
 * per eliminare un eventuale byte di "a capo").
 *
 * - Se s2 è contenuta all’interno di s1, il programma stampa la parte
 *   di s1 che segue s2.
 *
 * - Se s2 non è contenuta all’interno di s1, non stampa niente.
 * 
 * IMPORTANTE:  Per  massimizzare  l'apprendimento, si  raccomanda  di
 * leggere  la  soluzione  proposta  soltanto *dopo*  aver  provato  a
 * risolvere il problema autonomamente.
 */

#include <stdio.h>

int main()
{
	/* 
	 * If up to 80 characters are read, then 81 must be allocated,
	 * to store the terminating 0 as well.
	 */
	char s1[81], s2[81];
	char * p, i=0;

	/* Reading both s1 and s2 from stdin */
	printf("Enter s1:\n");
	fgets(s1,sizeof(s1),stdin);
	printf("Enter s2:\n");
	fgets(s2,sizeof(s2),stdin);

	/* Search for first non-printable character and close the string */
	for (p = s1; (32 <= *p) && (*p <= 126); p++);
	*p = 0;
	for (p = s2; (32 <= *p) && (*p <= 126); p++);
	*p = 0;

	/* Scanning s1 */
	for (p = s1; *p; p++) {
		if (*(s2+i) == 0) {
			/* 
			 * Reached end of s2. p points to the string
			 * after s1
			 */
			break;
		}
		if (*(s2+i) == *p) {
			/* same characters, advance in s2 */
			i++;
		} else if (*s2 == *p) {
			/* found the beginning of a new s2 */
			i = 1;
		} else {
			/* different characters, reset */
			i = 0;
		}
	}

	/* Now printing */
	printf("String in s1, after s2 is:\n%s\n", p);

	return 0;
}
