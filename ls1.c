#include "shell.h"
/**
 * list_len - Calculates the length of a linked list.
 * @h: Pointer to the first node of linked list.
 * Return: Size of linked list.
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
 * list_to_strings - Convert  linked list to an array of str
 * @head: Pointer to first node of the linked list
 * Return: Array of strings.
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
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to first node of the linked list.
 * Return: Size of linked list.
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
 * node_starts_with - Returns the node whose string starts with a prefix.
 * @node: Pointer to head of the linked list.
 * @prefix: String to match thee start.
 * @c: The next character after the prefix to match.
 * Return: The matched node or NULL if no match is found.
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
 * get_node_index - Gets the index of a node i linked list
 * @head: Pointer to the head of linked list.
 * @node: Pointer to the node whose index is to be found.
 * Return: index of the node or -1 if the node is not found in the list.
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
