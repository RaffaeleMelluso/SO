#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[20];   /* String to read integers */
	int  v[7], i, len;
	
	len = sizeof(v)/sizeof(v[0]);  /* Length of array from its size */	
	printf("Enter %d numbers\n", len);
	for(i=0; i < len; i++) {
		fgets(s, sizeof(s), stdin);
		v[i] = strtol(s, NULL, 10);
	}
	printf("Printing in the required order\n");
	for(i=0; i < len; i += 2)
		printf("%d\n", v[i]);
	for(i=1; i < len; i += 2)
		printf("%d\n", v[i]);
}
