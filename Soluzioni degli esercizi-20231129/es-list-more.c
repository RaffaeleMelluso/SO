#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Elimina tutti gli elementi con valore inferiore a cut_value
 */
list list_cut_below(list head, int cut_value );

/*
 * Copia tutta una lista (elemento per elemento)
 */
list list_dup(list head);

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
	 * viene passato un solo parametro. Approfondimento:
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

list list_delete_if(list head, int to_delete)
{
	list p = head, q;

	/* Lista vuota */
	if (head == NULL) {
		return NULL;
	}

	/* Elemento da cancellare in testa */
	if (head->value == to_delete) {
		head = head->next;
		free(p);
		return head;
	}

	/* Ciclo alla ricerca dell'elemento con value == to_delete */ 
	for (p = head; p->next != NULL; p = p->next) {
		if (p->next->value == to_delete) {
			/* Trovato elemento da cancellare */
			q = p->next->next;   /* puntatore al resto della lista*/
			free(p->next);       /* dealloca */
			p->next = q;         /* aggancia resto della lista */
			break;               /* esci dal for */
		}
	}
	return head;         /* fine */
}

list list_delete_odd(list head)
{
	list p;
	
	/* Lista vuota */
	if (head == NULL) {
		return NULL;
	}

	p = head->next;
	free(head);
	/* Lista head di un solo elemento */
	if (p == NULL) {
		return NULL;
	}

	/* Chiamata ricorsiva */
	p->next = list_delete_odd(p->next);
	return p;
}

list list_cut_below(list head, int cut_value)
{
	list p;
	
	if (head == NULL) {
		/* Niente da fare. Soltanto return NULL */
		return NULL;
	}
	if (head->value < cut_value) {
		/* Dobbiamo tagliare/deallocare il nodo puntato da head */
		p = head->next;
		free(head);
		return list_cut_below(p, cut_value);
	} else {
		head->next = list_cut_below(head->next, cut_value);
		return head;
	}
}

list list_dup(list head)
{
	list new;
	
	if (head == NULL) {
		return NULL;
	}
	/*
	 * Allocazione di un nuovo nodo su cui copiare il nodo puntato
	 * da head
	 */
	new = malloc(sizeof(*new));
	/* 
	 * memcpy funziona anche in caso di nodo realizzato da struct
	 * generica. Nel caso particolare di nodo contenente un int,
	 * va bene anche
	 *
	 * new->value = head->value;
	 */
	memcpy(new, head, sizeof(*new));
	new->next = list_dup(head->next);
	return new;
}
