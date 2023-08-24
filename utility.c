#include "shell.h"
/**
 * _interactive - if the shell is interactive mode it returns true
 * @info: Pointer to p_info_t struct.
 * Return: 1 if shell is in is interactive mode, 0 otherwise.
 */
int _interactive(p_info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - Checks if a character is a seperator
 * @c: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if the character is a seperator, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - Checks if a character is an alphabetic
 * @c: The character to be checked
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - Converts  string to integer.
 * @s: The string to converted.
 * Return: 0 if there are no numbers in the string,
 * the converted number otherwise.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
