/*
 * Try the following commands
 *
 *   gcc -E test-preproc.c
 *
 * and check stdout.
 * How to scroll the output slowly? How to redirect stdout to a file?
 * Now try
 *
 *   gcc -E -D GOOD test-preproc.c
 *
 * and try also
 *
 *   gcc -E -D GOOD -D A=4 test-preproc.c
 *
 * Try to change the "#if 1" in "#if 0" to see the differences.
 * Now invoke
 *
 *   echo -e -n "my fake header\n" > stdio.h
 *
 * and compare the output of the next two commands
 *
 *   gcc -E test-preproc.c
 *   gcc -E -D MY_SPECIAL_STDIO test-preproc.c
 * 
 * To check the pre-defined macros, try
 *
 *   gcc -E -D DEBUG test-preproc.c
 * 
 * how are __FILE__, __LINE__, #v and v expanded?
 */


#ifdef GOOD
#define SOMMA(x,y)  (x+y)
#else
#define SOMMA(x,y)  x+y
#endif

#define PI 3.1454

a = PI*SOMMA(A,3);

#define SQUARE(x)  (x*x)

b = SQUARE(SQUARE(y))

#define MY_DEBUG_CODE(v) printf("We are at line %i in file \"%s\". Value of \"%s\" is %i\n", \
			     __LINE__, \
			     __FILE__,\
			     #v, v)

#ifdef DEBUG
  MY_DEBUG_CODE(var1);
  MY_DEBUG_CODE(var2);
#endif

#if 1
testo prima
#else
testo dopo
#endif

#ifndef  MY_SPECIAL_STDIO
#include <stdio.h>
#else
#include "stdio.h"
#endif

