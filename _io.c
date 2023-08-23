#include "shell.h"
/**
 * _eputs - prints an inputas the string
 * @str: The string to be printed.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 * Return: On success, 1 On error, -1 is returned.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[SIZE_BUF_WRITE];

	if (c == FLUSH_BUF || i >= SIZE_BUF_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUF)
		buf[i++] = c;
	return (1);
}
/**
 * _putfd - Writes the character c to the file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success, 1 On error, -1 is returned.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[SIZE_BUF_WRITE];

	if (c == FLUSH_BUF || i >= SIZE_BUF_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUF)
		buf[i++] = c;
	return (1);
}
/**
 * _putsfd - Prints an input string to the fd
 * @str: string to be printed.
 * @fd: file descriptor to write to.
 * Return: number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
