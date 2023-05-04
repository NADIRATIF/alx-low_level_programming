#include "main"

 /**
 * set_bit - sets the value of a bit to 1 at a given index.
 * @index: the index of the bit you want to set, starting from 0
 * @n: a pointer to the number whose bit you want to set
 * Return: 1 if the bit was successfully set, or -1 if an error occurred
 **/
int set_bit(unsigned long int n, unsigned int index)
{
	/* Check if the index is valid for the unsigned long integer */
	if (index > (sizeof(unsigned long int) * 8 - 1))
		return (-1);

	/* Shift 1 by the index to get a value with a 1 at the desired bit position */
	unsigned long int m = 1UL << index;
	/* Use bitwise OR to set the bit at the desired position to 1 */
	*n |= m;
	return (1);
}
