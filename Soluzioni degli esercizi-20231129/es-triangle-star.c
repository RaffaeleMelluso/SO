#include <stdio.h>
#include <stdlib.h>

int main()
{
	int b, h, i, j, len;
	char s[20];
	
	printf("Inserire altezza: \t");
	fgets(s, sizeof(s), stdin);
	h = strtol(s, NULL, 10);
	if (h <= 1) {
		printf("L\'altezza deve essere >= 1\n");
		return 0;
	}
	printf("Inserire base: \t");
	fgets(s, sizeof(s), stdin);
	b = strtol(s, NULL, 10);
	if (b <= 0) {
		printf("La base deve essere positiva\n");
		return 0;
	}
	/* Primo vertice si stampa sempre */
	for(i=1; i<=h; i++) {
		len = ((b-1)*i+h-b)/(h-1);
		for(j=1; j<=len; j++) printf("*");
		printf("\n");
	}
	
	/* stampa dei numeri per contare */
	for(j=1; j<=b; j++) printf("%1d", j / 10);
	printf("\n");
	for(j=1; j<=b; j++) printf("%1d", j % 10);
	printf("\n");

}
