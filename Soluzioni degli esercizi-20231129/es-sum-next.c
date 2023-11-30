#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[20];   /* String to read integers */
	int  v1[10], v2[10], i, len;
	
	len = sizeof(v1)/sizeof(v1[0]);  /* Length of array from its size */	
	printf("Enter %d numbers\n", len);
	for(i=0; i < len; i++) {
		fgets(s, sizeof(s), stdin);
		v1[i] = strtol(s, NULL, 10);
	}
	for(i=len-1, v2[i]=v1[i], i--; i >= 0; i--) {
		v2[i] = v2[i+1]+v1[i];
	}
	
	printf("Printing in the required order\n");
	for(i=0; i < len; i++)
		printf("%d\n", v2[i]);
}
