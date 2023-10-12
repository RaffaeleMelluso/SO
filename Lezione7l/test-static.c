#include <stdio.h>

/* c1 is global variable, allocated over the BSS */
int c1 = 100;

void func() {
	/* c2 is allocated over the stack */ 
	int c2 = 10;
	/* c3 is allocated over the BSS, but visible only within the
	 * function */
	static int c3 = 1;
	
	printf("func: c1=%2d,   c2=%2d,   c3=%2d\n", c1, c2, c3);
	c1++;
	c2++;
	c3++;
}

int main(int argc, char *argv[])
{
	int i;
	
	/* 
	 * Questa istruzione genera errore: c3 e` static ma non
	 * global!
	 */
	/* printf("main: c3 %d\n", c3); */
	
	for (i = 0; i < 5; i++) {
		func();
	}
	
	return 0;
}
