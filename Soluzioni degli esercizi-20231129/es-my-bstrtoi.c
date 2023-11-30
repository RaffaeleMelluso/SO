#include <stdio.h>
#include <stdlib.h>

int main() {
	char string[200];
	char buffer[30];
	int i = 0;
	int retnum = 0;
	int sign;
	int flag = 1;
	int base;

	printf("Inserisci la stringa: \n");

	if(fgets(string, sizeof(string), stdin) == NULL) {
		printf("Error, bad string input\n");
		return -1;
	}

	printf("Inserisci la base: \n");

	if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
		printf("Error, bad string input\n");
		return -1;
	}

	base = atoi(buffer);

	if(base < 2 || base > 36){
        printf("Wrong base\n");
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

	for(; string[i] != '\n' && string[i] != '\0' && flag == 1; i++)  {
        int digit;

        if(string[i] >= '0' && string[i] <= '9')
            digit = string[i] - '0';
        else if(string[i] >= 'A' && string[i] <= 'Z')
            digit = string[i] - 'A' + 10;
        else
            flag = 0;

        /* if digit is not in [0, base) then error*/
        if(digit < 0 || digit >= base)
            flag = 0;

        retnum = retnum * base + digit;
    }

	if(flag == 1) {
		printf("String represents %d\n", retnum * sign);
	} else
		printf("String doesn't represent a number in specified base\n");

    return 0;
}