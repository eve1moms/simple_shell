#include "shell.h"
/**
 * my_history - shows history list, Showing 1 cmd per line,
 * proceding with line numbers starting at 0.
 * @info: This is the Struct that has potential arguments that
 * maintains THE C onstantFunct prototype.
 * Return: 0
 */
int my_history(p_info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - inside the string, it delete an alias associated with it
 * @str: STR to del
 * @info: Parameter STRUCT
 * Return: 0 on succes ELSE 1 on error.
 */
int unset_alias(p_info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * set_alias - in the string it sets an alias
 * @str: STR where alias is to be set
 * @info: Parameter STRUCT
 * Return:  0 on success, 1 on error.
 */
int set_alias(p_info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - this fuction rpints the alis strung
 * @node: this is the alis node to be printed
 * Return: 0 on success ELSE 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_alias - this funct mimics the alias builtin,(man alias)
 * @info: This contains potential arg
 * and it maintain a constant prototype
 * Return: 0.
 */
int my_alias(p_info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
