#include "shell.h"
/**
 * _interactive - if the shell is interactive mode it returns true
 * @info: this is the Pointer 2 p_info_t struct.
 * Return: if the SHELL is in interacive mode 1 else 0
 */
int _interactive(p_info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - this function checks if the charpresent is a seperatore
 * @delim: this is the str delimeer
 * @c: This is the caharacter to check.
 * Return: if THEchar is SEPERRATPR
 */
int is_delim(char c, char *delim)
{

	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - this function  Checks if  chars is ALPHABETIC
 * @c: This is the char to be checked
 * Return:if characyer is alphabeti 1 else 0c
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - this function converts a STRG to an int.
 * @s: This is the str to be converted.
 * Return: if there are no number 0 else the number converted
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
