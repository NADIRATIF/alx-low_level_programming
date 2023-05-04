#include "main.h"

/**
 * get_bit - returns the value of a bit at a given index.
 * @n: checking bits
 * @index: which to check bit
 *
 * Return: the value of the bit at index
 */
int get_bit(unsigned long int n, unsigned int i)
{
	unsigned long int d, r;

	if (i > (sizeof(unsigned long int) * 8 - 1))
		return (-1);
	d = 1 << i;
	r = n & d;
	if (r == d)
		return (1);

	return (0);
}
