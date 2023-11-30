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

int main()
{
	list head = NULL, l2 = NULL;

	/* Inserisci alcuni valori a caso */
	head = list_insert_tail(head,15);
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_tail(head,17);
	list_print(head);
	head = list_insert_ordered(head, 1);
	list_print(head);
	head = list_insert_ordered(head, 20);
	list_print(head);
	head = list_insert_ordered(head, 13);
	l2 = list_insert_ordered(l2, 50);
	list_print(l2);
	head = list_cat(head, l2);
	list_print(head);
	list_free(head);

	return 0;
}

list list_insert_head(list p, int val)
{
	list new_el;

	/* Alloca e inizializza il nuovo elemento */
	new_el = malloc(sizeof(*new_el));
	new_el->value = val;
	/* Appendi la vecchia lista in coda al nuovo elemento */
	new_el->next = p; 
	return new_el;
}

void list_print(list p)
{
	if (p == NULL) {
		printf("Empty list\n");
		return;
	}
	for(; p; p = p->next) {
		printf("-> %i ", p->value);
	}
	printf("\n");
}

void list_free(list p)
{
	if (p == NULL) {
		return;
	}
	/* 
	 * Versione ricorsiva: (1) fai list_free dei prossimi
	 * elementi, poi (2) dealloca l'elemento corrente
	 */
	list_free(p->next);
	free(p);
}

/* Versione ricorsiva */
list list_insert_ordered(list p, int val)
{
	if (p == NULL) {
		/* lista vuota: inserisci in testa */
		return list_insert_head(p, val);
	}
	/* Da qui in poi, la lista non e` vuota */
	if (val <= p->value) {
		/* val e` il minimo: inserisci in testa */
		return list_insert_head(p, val);
	}
	/* Dobbiamo passare al prossimo elemento */
	p->next = list_insert_ordered(p->next, val);
	return p;
}

/* Versione iterativa */
list list_cat(list before, list after)
{
	list p_iter;

	if (before == NULL) {
		return after;
	}
	/* Scorri fino a quando p_iter->next e` NULL */
	for (p_iter = before; p_iter->next; p_iter = p_iter->next);

	/* Concatena le due liste */
	p_iter->next = after;
	return before;
}

list list_insert_tail(list p, int val)
{
	if (p == NULL) {
		/* Se p e` NULL, ins. in coda = ins. in testa */
		return list_insert_head(p, val);
	}
	/* Scorri la lista ricorsivamente fino in fondo */
	p->next = list_insert_tail(p->next, val);
	return p;
}
