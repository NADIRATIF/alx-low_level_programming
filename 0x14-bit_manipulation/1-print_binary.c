#include "main.h"
/**
 * _pwr - calculate the base and power
 * @b: base of the exponet
 * @p: power of the exponet
 * Return: value of base and power
 */
unsigned long int _pwr(unsigned int b, unsigned int p)
{
	unsigned long int n;
	unsigned int x;

	n = 1;
	for (x = 1; x <= p; x++)
		n *= b;
	return (n);
}
/**
 * print_binary - prints the binary representation of a number
 * @n: n of prented
 * Return: void
 */
void print_binary(unsigned long int n)
{
	unsigned long int d, r;
	char f;

	f = 0;
	d = _pwr(2, sizeof(unsigned long int) * 8 - 1);

	while (d != 0)
	{
		r = n & d;
		if (r == d)
		{
			f = 1;
			_putchar('1');

		}
		else if (f == 1 || d == 1)
		{
			_putchar('0');
		}
		d >>= 1;
	}
}
