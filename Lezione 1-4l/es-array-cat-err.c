#include <stdio.h>
#include <string.h>
/* Codice che concatena le due stringhe v1 e v2 */
int main()
{
	char v1[20] = "Prima,";
	char v2[10] = " dopo";
	int len1, len2, i;
	
	 /* Lunghezza delle due stringhe */
	len1 = strlen(v1);
	len2 = strlen(v2);

	/* Stampa delle due stringhe */
	printf("%s %d\n", v1, len1);
	printf("%s %d\n", v2, len2);	

	/* Copia la seconda stringa alla fine della prima */
	for (i=0; i<len2 ; i++)
		v1[len1+i] = v2[i];
	/* Stampa la stringa concatenata */
	printf("%s\n", v1);
	return 0;
}
