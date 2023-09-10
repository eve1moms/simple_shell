#include "shell.h"
/**
 * _strncpy - This is supposed to copy a string
 * @n: the no of character to be copied.
 * @src: this isthe sourxe str
 * @dest: this is the destination string to be copied to
 * Return: A POinter to de destinaoon string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 * _strncat - this concatenates(combines) two strings
 * @src: this is the 2nd part of the string
 * @dest:  this is the scecond string
 * @n: this sis the ma no f ytes to use
 * Return: should retuen a pointer to the concatenateds tring
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
/**
 * _strchr - this finds STR
 * @c: this is thecharater to look for
 * @s: this is the sring to persey.
 * Return: Aponter to the memory
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
