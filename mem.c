#include "shell.h"
/**
 * bfree - this funcion frees a POINTER address and then ses it 2 NULL
 * Note: it checksif pointer is not NULLL b4 atempting 2 free it
 * @ptr: this is the adress o pointer to free
 * Return: if the memory is freeed sucessfully return 1 else 0
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
