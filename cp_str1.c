#include "shell.h"
/**
 * _strcpy - Copies a src string to a dest string.
 * @dest: The dest string.
 * @src: The src string.
 * Return: Pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _strdup - Duplicates a string.
 * @str: string to duplicate.
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	/* Function to duplicate a given string */
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 * _puts - Prints an input string.
 * @str:string to be printed.
 */
void _puts(char *str)
{
	/* Function to print the given string */
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * _putchar - Writes the character c to stdout.
 * @c: character to print.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	/* Function to write a character to stdout */
	static int i;
	static char buf[SIZE_BUF_WRITE];

	if (c == FLUSH_BUF || i >= SIZE_BUF_WRITE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUF)
		buf[i++] = c;
	return (1);
}
