#include "lists.h"
#include <stdio.h>

/**
 * print_dlistint - prints all elements of a dlistint_t list.
 * @h: head of a doubly linked list
 * Return: number of nodes
 */

size_t print_dlistint(const dlistint_t *h)
{
	const dlistint_t *ptr = h;
	size_t n = 0;

	while (ptr != NULL && ptr->prev != NULL)
		ptr = ptr->prev;
	while (ptr != NULL)
	{
		printf("%d\n", ptr->n);
		n++;
		ptr = ptr->next;
	}
	return n;
}

