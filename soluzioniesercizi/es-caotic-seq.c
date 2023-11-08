#include <stdio.h>

/*
 * Compile it with flag -D PRINT_SEQ to also print the sequence
 */

int count_caotic_seq(int n)
{
	int i=1	;
	
	if (n <= 0) {
#ifdef  PRINT_SEQ
		printf("Non-positive initial number: empty sequence\n");
#endif
		return 0;
	}
	while (n!=1) {
#ifdef  PRINT_SEQ
		printf("%d, ", n);
#endif
		if (n % 2) {
			/* n dispari */
			n = 3*n+1;
			if (n <= 0) {
				printf("OVERFLOW!!\n");
				return i;
			}
		} else {
			/* n pari */
			n >>= 1;    /* divisione per 2 con shift */
		}
		i++;
	}
#ifdef  PRINT_SEQ
	printf("1\n");
#endif
	return i;	
}


int main()
{
	int n_max, i;
	
	printf("Insert the number of sequences to be tested: ");
	scanf("%d", &n_max);
	for(i=1; i<=n_max; i++) {
		printf("start, num: %d, %d\n", i, count_caotic_seq(i));
	}
}
