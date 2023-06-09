#include "main.h"

/**
 * set_bit - sets the value of a bit to 1 at a given index.
 * @n: a pointer to the unsigned long integer whose bit you want to set
 * @index: the index of the bit you want to set, starting from 0
 * Return: 1 if the bit was successfully set, or -1 if an error occurred
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int x;

	if (index > (sizeof(unsigned long int) * 8 - 1))
		return (-1);
	x = 1 << index;
	*n = *n | x;

	return (1);
}
