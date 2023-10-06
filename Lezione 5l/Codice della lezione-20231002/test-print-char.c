#include <stdio.h>

int main()
{
	int a;

	/* What is the value of the following constant? */
	a = '7';
	printf("The value of \'7\' is\n%%d=%d\t(decimal)\n%%02X=%02X\t(hex)\n%%c=%c\t(ASCII character)\n", a, a, a);

	return 0;
}
