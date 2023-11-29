#include <stdio.h>  /* FIXED (easy): necessario per usare printf */
#include <string.h>  /* FIXED (easy): necessario per usare printf */


/* Codice che concatena le due stringhe v1 e v2 */
int main()
{
	/* FIXED (easy): aggiunti punto e virgola */
	char v1[12] = "Prima,";	/* FIXED (hard): dimensione di v1 va modificata per contenere anche v2.
				 * Almeno 12 bytes. Se non viene fatto, quando si scrive su v1, si finisce
				 * per scrivere anche su quello che segue (v2 nel mio caso) */
	char v2[10] = " dopo";
	int len1, len2, i;
	
	 /* Lunghezza delle due stringhe */
	/* FIXED (medium): sizeof NON e` lunghezza. Va calcolata a mano, anche strlen va bene */
	for (len1 = 0; v1[len1]; len1++);
	for (len2 = 0; v1[len2]; len2++);

	/* Stampa delle due stringhe */
	printf("%s\n", v1);     /* FIXED (easy): stampa di stringa con %s invece che %d */
	printf("%s\n", v2);	/* FIXED (easy): stampa di stringa con %s invece che %d */

	/* Copia la seconda stringa alla fine della prima */
	for (i=0; i<len2; i++)
		v1[len1+i] = v2[i];
	v1[len1+len2] = 0;	/* FIXED (hard): stringa v1 va chiusa con lo zero */
	
	/* Stampa la stringa concatenata */
	printf("%s\n", v1);	/* FIXED (easy): stampa di stringa con %s invece che %d */
	
}
