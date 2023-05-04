#include "main.h"

/**
 * flip_bits - calculates the number of bits that need to be flipped to get from one number to another.
 * @n: the first number
 * @m: the second number
 * Return: the number of bits that need to be flipped
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int d, r;
	unsigned int y, x;

	y = 0;
	r = 1;
	d = n ^ m;
	for (x = 0; x < (sizeof(unsigned long int) * 8); x++)
	{
		if (r == (d & r))
			y++;
		r <<= 1;
	}

	return (y);
}
