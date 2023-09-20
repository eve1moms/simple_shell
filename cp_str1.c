#include "shell.h"
/**
 * _strcpy - this copied a src str to destination string
 * @src: this is the source string
 * @dest: this is the destination string
 * Return:a pointer to the s dest string
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
 * _strdup - This is dupposed to duplicate a string
 * @str: String that is supposed to be duoplcated
 * Return: A pointer to the duplicated string
 */
char *_strdup(const char *str)
{
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
 * _puts - This prints out an input string
 * @str: String that is supossed to be printed
 */
void _puts(char *str)
{
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
 * _putchar - This writes a Char c to STDOut
 * @c: This is the character to print out
 * Return: 1 on sucess  0  when fail and errno isset approprietly
 */
int _putchar(char c)
{
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
