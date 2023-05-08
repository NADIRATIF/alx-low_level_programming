#include "main.h"

/**
 * _strlen - look for the length of a string
 * @str: pointer string
 *
 * Return: size length of the string
 */
size_t _strlen(char *str)
{
	size_t i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}

/**
 * append_text_to_file - function that appends text 
 * at the end of a file.
 * @filename: name of the file
 * @text_content: NULL terminated string to add at the end of the file
 *
 * Return: 1 or -1
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int op;
	ssize_t l;

	if (filename == NULL)
		return (-1);
	op = open(filename, O_WRONLY | O_APPEND);
	if (op == -1)
		return (-1);
	if (text_content != NULL)
		l = write(op, text_content, _strlen(text_content));
	close(op);
	if (l == -1)
		return (-1);
	return (1);
}
