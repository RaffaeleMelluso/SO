#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;

typedef node* list;

/*
 * Assume that the list is in increasing order and insert the element
 * preserving the increasing order
 */
list list_insert_ordered(list p, int val)
{
	while(val<p->value){
		p=p->next;
	}

	node new_node,*tmp, *p_new=&new_node;
	new_node.value=val;
	tmp=p->next;
	p->next=p_new;
	p_new->next=tmp;
	return p;

}

/*
 * Concatenate two lists
 */
list list_cat(list before, list after)
{
	while (before->next!=NULL)
	{
		before=before->next;
	}
	before->next=after;
	return before;
}
/*
 * Insert elements at the head of the list
 */
list list_insert_head(list p, int val)
{
	list new;
	new->value=val;
	new->next=p;
	return new;
}
/*
 * Insert elements at the tail of the list
 */
list list_insert_tail(list p, int val)
{
	while (p->next!=NULL)
	{
		p=p->next;
	}
	node new;
	new.value=val;
	new.next=NULL;
	p->next=&new;
	return p;
}

/*
 * Print the list content
 */
void list_print(list p)
{
	while (p->next!=NULL)
	{
		printf("%d->",p->value);
	}
	
}

/*
 * Free the list
 */

void list_free(list p)
{
	free(p);
}

int main()
{
	list head = NULL;

	/* insert some numbers in the list... */
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head =  (head, 15);
	/* ... print them... */
	list_print(head);
	/* ... and clean everything up  */
	list_free(head);

	return 0;
}

list list_insert_head(list p, int val)
{
	list new_el;

	/* Allocate the new node */
	new_el = malloc(sizeof(*new_el));
	/* Setting the data */
	new_el->value = val;
	/* head insertion: old head becomes .next field of new head */
	new_el->next = p;
	/* new head is the pointer to the new node */
	return new_el;
}

void list_print(list p)
{
	/* Looping all nodes until p == NULL */
	if (p == NULL) {
		printf("Empty list\n");
		return;
	}
	printf("[%i]", p->value);
	for(; p->next!=NULL; p = p->next) {
		printf(" -> [%i]", p->next->value);
	}
	printf("\n");
}

void list_free(list p)
{
	/* If p ==  NULL, nothing to deallocate */
	if (p == NULL) {
		return;
	}
	/* First deallocate (recursively) the next nodes... */
	list_free(p->next);
	/* ... then deallocate the node itself */
	free(p);
}
