#include "shell.h"
/**
 * _strlen - this funcion returns the len(length)of a string
 * @s: this is the string
 * Return: it returns the length of the str
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * _strcmp - thus funcion performs lexicographic comparison of 2 strings.
 * @s1: this is string number 1
 * @s2: the second string
 *  Return: if (-ve) s1 < s2, if (+) s1 > s2, if zero s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - tis function  checks if the  needle starts with HAYSTAC
 * @needle: this is the substring to find
 * @haystack: this is the string to find
 * Return: This returns an adress of the next CHAR of haystack
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - this function concatenates strings
 * @src: this  is the source buf
 * @dest: this is the destination buf
 * Return: should return a pointer to a dest buf
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
