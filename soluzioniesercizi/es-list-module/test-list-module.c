#include "list-module.h"

/*
 * Macro  del  preprocessore che  permette  in  modo compatto  di  (1)
 * stampare la chiamata  che ci si appresta ad  eseguire, (2) invocare
 * la  funzione  richiesta  e  (3)  stampare  la  lista  eventualmente
 * modificata dopo l'invocazione.
 *
 * Parametri:
 *   list,  puntatore alla lista su cui operare
 *   call,  nome della funzione da invocare
 *   param, parametro dell'invocazione
 */
#define VERBOSE_CALL(list,call,param)					\
	printf("%s = %s(%s,%s)\n", #list, #call, #list, #param);	\
	list = call(list,param);					\
	list_print(list);

int main()
{
	list head = NULL, l2 = NULL;

	/* Inserisci alcuni valori a caso */
	VERBOSE_CALL(head,list_insert_tail,15);
	VERBOSE_CALL(head,list_insert_head,10);
	VERBOSE_CALL(head,list_insert_head,2);
	VERBOSE_CALL(head,list_insert_tail,17);
	VERBOSE_CALL(head,list_insert_ordered,1);
	VERBOSE_CALL(head,list_insert_ordered,20);
	VERBOSE_CALL(head,list_insert_ordered,13);
	VERBOSE_CALL(l2,list_insert_ordered,50);
	VERBOSE_CALL(head,list_cat,l2);
	VERBOSE_CALL(head,list_delete_if,19);
	VERBOSE_CALL(head,list_delete_if,50);
	VERBOSE_CALL(head,list_delete_if,13);
	VERBOSE_CALL(head,list_delete_if,1);
	/* 
	 * La macro VERBOSE_CALL si puo` usare solo con chiamate a cui
	 * viene passato uno un parametro. Approfondimento:
	 * investigare "variadic macros" at
	 *
	 * https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
	 */
	printf("head = list_delete_odd(head)\n");
	head = list_delete_odd(head);
	list_print(head);
	VERBOSE_CALL(head,list_insert_ordered,1);
	VERBOSE_CALL(head,list_insert_ordered,20);
	VERBOSE_CALL(head,list_insert_ordered,13);
	VERBOSE_CALL(head,list_cut_below,13);
	printf("l2 = list_dup(head)\n");
	l2 = list_dup(head);
	list_print(l2);
	list_free(l2);
	list_free(head);

	return 0;
}
