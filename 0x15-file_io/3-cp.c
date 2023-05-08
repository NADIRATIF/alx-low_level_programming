#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * ck97 - checker for the correct number of arguments
 * @a: number of arguments
 *
 * Return: void
 */
void ck97(int a)
{
	if (a != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
}

/**
 * ck98 - checker for that file_from exists and can be read
 * @c: checks if true of false
 * @f: file_from name
 * @f_from: file_from, or -1
 * @f_to: file_to, or -1
 *
 * Return: void
 */
void ck98(ssize_t c, char *f, int f_from, int f_to)
{
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", f);
		if (f_from != -1)
			close(f_from);
		if (f_to != -1)
			close(f_to);
		exit(98);
	}
}

/**
 * ck99 - checker for that file_to was created and/or can be written to
 * @c: checks if true of false
 * @f: file_to name
 * @f_from: file_from, or -1
 * @f_to: file_to, or -1
 *
 * Return: void
 */
void ck99(ssize_t c, char *f, int f_from, int f_to)
{
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", f);
		if (f_from != -1)
			close(f_from);
		if (f_to != -1)
			close(f_to);
		exit(99);
	}
}

/**
 * ck100 - checker for  that file descriptors were closed properly
 * @c: checks if true or false
 * @f: file
 *
 * Return: void
 */
void ck100(int c, int f)
{
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", f);
		exit(100);
	}
}
/**
 * main - copies the content of a file to another file.
 * @argc: number of arguments passed
 * @argv: can be array of pointers to the arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int f_from, f_to, c_to, c_from;
	ssize_t lr, lw;
	char b[1024];
	mode_t f_perm;

	ck97(argc);
	f_from = open(argv[1], O_RDONLY);
	ck98((ssize_t)f_from, argv[1], -1, -1);
	f_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	f_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, f_perm);
	ck99((ssize_t)f_to, argv[2], f_from, -1);
	lr = 1024;
	while (lr == 1024)
	{
		lr = read(f_from, b, 1024);
		ck98(lr, argv[1], f_from, f_to);
		lw = write(f_to, b, lr);
		if (lw != lr)
			lw = -1;
		ck99(lw, argv[2], f_from, f_to);
	}
	c_to = close(f_to);
	c_from = close(f_from);
	ck100(c_to, f_to);
	ck100(c_from, f_from);
	return (0);
}
