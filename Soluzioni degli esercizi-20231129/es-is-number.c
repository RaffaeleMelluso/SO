#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_LEN 5

int main() {
	char string[MAX_LEN];
	char buffer[30];
	int a, b, i;
	int flag = 1; /* until disproven, string represents a number */

	printf("Inserisci la stringa lunga al piu` %d:\n", MAX_LEN-2);

	if(fgets(string, sizeof(string), stdin) == NULL) {
		printf("Error, no string entered\n");
		return -1;
	}

	/* MAX_LEN-3 perche' non contiamo lo zero di terminazione
	  il carattere \n e perche' le posizioni si contano da zero */ 
	printf("Inserisci \"a\" fra %d e %d:\n", 0, MAX_LEN-3);
	if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
		printf("Error, nothing entered\n");
		return -1;
	}

	a = strtol(buffer, NULL, 10);

	printf("Inserisci \"b\" fra %d e %d:\n", a, MAX_LEN-3);
	if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
		printf("Error, nothing entered\n");
		return -1;
	}

	b = strtol(buffer, NULL, 10);


	if(a > b || a < 0 || b > MAX_LEN-1){
		printf("Invalid range a=%d, b=%d entered\n", a, b);
		return -1;
	}

	if (string[a] != '\0' && (string[a] == '-' || string[a] == '+'))
		a++;

	for (i = a; i <= b && flag == 1; i++) {
		if (string[i] < '0' || string[i] > '9') {
			/* Substring doesn't represent a number */
			flag = 0;
		}
	}

	if(flag == 0) {
		printf("Substring is not a number\n");
	}
	else {
		printf("Substring is a number\n");
	}

}
