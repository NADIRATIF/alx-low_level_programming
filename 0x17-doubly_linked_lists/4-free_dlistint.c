#include "lists.h"
#include <stdio.h>

/**
 * free_dlistint - frees a list
 * @head: pointer to the start of the list
 * Return: nothing
 */
void free_dlistint(dlistint_t *head)
{
	dlistint_t *new;

	while (head != NULL)
	{
		new = head->next;
		free(head);
		head = new;
	}
}
