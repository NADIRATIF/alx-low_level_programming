#include "main.h"

/**
 * clear_bit - sets the value of a bit to 0 at a given index.
 * @n: a number whose bit you want to clear
 * @index: the index of the bit you want to clear, starting from 0
 * Return: 1 if the bit was successfully cleared, or -1 if an error occurred
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int x;

	if (index > (sizeof(unsigned long int) * 8 - 1))
		return (-1);
	x = ~(1 << index);
	*n = *n & x;

	return (1);
}
