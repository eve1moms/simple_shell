#include "shell.h"
/**
 * is_chain - This checks if  achratcter ina buf is a chain delimeter
 * @buf: thhi sis the character buf
 * @info: this is the parameter
 * @p: this is the adress to the current buff positiion
 * Return: if is a cin delimeter return 1 else 0
 */
int is_chain(p_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = _OR_CMD;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = _AND_CMD;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = _CHAIN_CMD;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - this checks if the chaining shouls continue
 * based on the last ststus
 * @p: this shows he address of thh current position in buf
 * @len: this is the legth of the buf
 * @info: this is the pointer to the parameter struct
 * @buf: The character buffer.
 * @i: Starting position in buf.
 */
void check_chain(p_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == _AND_CMD)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == _OR_CMD)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}
/**
 * replace_alias - Thisis upposed to replace an alis to the supported string
 * @info: this is a pointrt to the parmeter s structure
 * Return: if replaced return 1 otherwise 0.
 */
int replace_alias(p_info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
/**
 * replace_vars - this is supposedto rrplace values in the tiokenised strng
 * @info:  this theb parameters struct
 * Return: if replaced 1 else 0
 */
int replace_vars(p_info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(num_to_str(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(num_to_str(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - this is supposed to replcace  a string
 * @new: this is the new str
 * @old:  this is the Address of the old str
 * Return: if replaced return 1 else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
