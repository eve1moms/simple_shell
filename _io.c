#include "shell.h"
/**
 * _eputs - this function prints an INPUT as the STR
 * @str: This is the string to be printed.
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
 * _eputchar -this function  Writes CHAR c 2 stderr.
 * @c: This is the character to be printed
 * Return: On success 1 iferror -1
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
 * _putfd - this function Writes the CHAR c 2 the fd
 * @fd: this is the file descriptor to be written 2
 * @c: This is the character to print.
 * Return: On sucess retuns 1 else on error -1
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
 * _putsfd - this this functionPrints an INPUT str 2 the fd
 * @fd: this is the file descriptor to b written 2
 * @str: this is the str to be printed
 * Return: the no of char put.
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
