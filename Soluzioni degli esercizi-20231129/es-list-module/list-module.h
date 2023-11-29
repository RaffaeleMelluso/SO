#ifndef _LIST_MODULE_H_
#define _LIST_MODULE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* Puntatore alla stessa struttura */
} node;

typedef node* list;

/*
 * Assume che la lista sia in ordine crescente e inserisce un elemento
 * con campo "value" uguale a val preservando l'ordinamento
 */
list list_insert_ordered(list p, int val);

/*
 * Concatena due liste
 */
list list_cat(list before, list after);

/*
 * Inserisce un elemento il testa alla lista
 */
list list_insert_head(list p, int val);

/*
 * Inserisce un elemento in coda alla lista
 */
list list_insert_tail(list p, int val);

/*
 * Stampa il contenuto della lista
 */
void list_print(list p);

/*
 * Dealloca la memoria occupata da ciascu elemento della lista
 */

void list_free(list p);

/*
 * Elimina e dealloca il primo nodo con valore to_delete
 */
list list_delete_if(list head, int to_delete);

/*
 * Elimina gli elementi in posizione dispari (primo, terzo, etc.). I
 * nodi si contano a partire da 1
 */
list list_delete_odd(list head );

/*
 * Elimina tutti gli elementi con valore inferiore a cut_value
 */
list list_cut_below(list head, int cut_value );

/*
 * Copia tutta una lista (elemento per elemento)
 */
list list_dup(list head);

#endif /* _LIST_MODULE_H_ */
