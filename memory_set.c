#include "shell.h"
/**
 * _memset - this function Fills MEMORYwith a constant BYTE
 * @b: this is the byte alue to fill
 * @s: this is a pointer 2 memory area
 * @n: This is the number of BYTES to fillnumber
 * Return: returns a pointr to thee memory adress s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - this function Frees an arr of str
 * @pp: This is the dynamic arr of str to be freed
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - this function reallocates block OF MEMEORY
 * @old_size: this is the previous size IN BYTES of BLOCK
 * @ptr: This is the pointer 2 previous mallocaed BLOCK
 * @new_size: This is NEW SIZE in byes of block
 * Return: void
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
