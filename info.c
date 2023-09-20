#include "shell.h"
/**
 * clear_p_info - this function initializes the fields of
 * p_info_t struct.
 * @info: this is the pointer 2 the p_info_t Strct 2 be initialized.
 */
void clear_p_info(p_info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_p_info - This function Initializes THE p_info_t Strct
 * then sets its fields
 * @av: this is the arg vectotor that will be used for initialization
 * @info: this is the pointer2 the p_info_t struct to be initialized then set.
 */
void set_p_info(p_info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = _strtop(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_p_info - This function Frees fields of the p_info_t struct
 * @all: free all the field if it is true else only the specific ones are freed
 * @info: this is the pointer 2 p_info_t
 */
void free_p_info(p_info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(FLUSH_BUF);
	}
}
