#include "main.h"
/**
 * create_file -function to create a file
 *
 * @text_content: NULL terminated string to write to the file
 * @filename: file name (the name of the file t create)
 *
 * Return: 1 or -1
 */
int create_file(const char *filename, char *text_content)
{
	int op, wr, l = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (l = 0; text_content[l];)
			l++;
	}

	op = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	wr = write(op, text_content, l);

	if (op == -1 || wr == -1)
		return (-1);

	close(op);

	return (1);
}
