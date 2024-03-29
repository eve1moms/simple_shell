#include "shell.h"
/**
 * my_env - this function prints the current enviroment
 * @info: This struct that has potential arg
 * Return: 0
 */
int my_env(p_info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - This get the value of the curentVarIABLE
 * @name: the name of the enviromentt variable
 * @info: this isthe structure containings potential args
 * Return: this function retrn value of te enirment varable else null
 */
char *_getenv(p_info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - thhis functio initializes a new enviroment variable
 * @info: This is the structure containing potential Args
 * Return: 0
 */
int _mysetenv(p_info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - this function deletes an envriment variable
 * @info: this is the strc containg potential arguments
 * it maintains a constant function prototype.
 * Return: 0.
 */
int _myunsetenv(p_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
/**
 * populate_env_list - tis function popultes the ENV lists
 * @info: this struct contains potential args.
 *it maintaincs a CONTANSTANT prototype.
 * Return: Constant 0
 */
int populate_env_list(p_info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
