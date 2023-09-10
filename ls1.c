#include "shell.h"
/**
 * list_len - this function  Calculates the len ofTHE linked list.
 * @h: this is the pointer 2 the 1st node of linked list.
 * Return: returns Size of linked list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * list_to_strings - this function Converts linked list 2 an [] of str
 * @head: this is Pointer to 1st node of the linked list
 * Return: [] of str
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - this function Prints ALLelements of list_t linked list.
 * @h: this is Pointer to 1st node of the linked list.
 * Return: returns Size of linked list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(num_to_str(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}
/**
 * node_starts_with - this function Returns
 * the node whose str STARTS with prefix.
 * @prefix: this is the string 2 match at the START
 * @node:this is the Pointer 2 Head of the linked list
 * @c: This is the The next CHAR after the prefix Matched
 * Return: returns the matched node lse NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);

		node = node->next;
	}

	return (NULL);
}
/**
 * get_node_index - this function Gets the INDEX of a node i linked list
 * @node: this is the ptr whise INDEX is to be found
 * @head: tis is a pointer to the head of the linked list.
 * Return: Returns index of the node else -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);

		head = head->next;
		i++;
	}

	return (-1);
}
