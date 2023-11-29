#include <stdio.h>

int main() {
	char string[200];
	int i = 0;
	int retnum = 0;
	int sign;
	int flag = 1;

	printf("Inserisci la stringa: \n");

	if(fgets(string, sizeof(string), stdin) == NULL) {
		printf("Error, bad string input\n");
		return -1;
	}

	if(string[0] == '-'){
		sign = -1;
	} else {
		sign = 1;
	}

	if (string[0] == '-' || string[0] == '+') {
		i++;
	}

	for(; string[i] != '\n' && string[i] != '\0' && flag == 1; i++) {
		if (string[i] >= '0' && string[i] <= '9') {
			retnum = retnum * 10 + (string[i] - '0');
		} else {
        		flag = 0;
        	}
	}

	if(flag == 1) {
		printf("String represents %d\n", retnum * sign);
	}
	else
		printf("String does not represent any number\n");

    return 0;
}
