#include "shell.h"
/**
 * bfree - Frees a pointer address  sets it to NULL.
 * @ptr: Address of the pointer to free.
 * Note: This function checks if the pointer is not
 *	NULL before attempting to free it.
 * Return: 1 if the memory is freed successfully else 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
