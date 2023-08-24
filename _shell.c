#include "shell.h"
/**
 * _shell - main shell loop.
 * @info: Pointer to the parameter and return info struct.
 * @av: argument vector from main().
 * The function runs the main loop of the shell.
 * Return: 0 on success, 1 on error, or an error code.
 */
int _shell(p_info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_p_info(info);
		if (_interactive (info))
			_puts("$ ");
		_eputchar(FLUSH_BUF);
		r = get_input(info);
		if (r != -1)
		{
			set_p_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (_interactive (info))
			_putchar('\n');
		free_p_info(info, 0);
	}
	write_history(info);
	free_p_info(info, 1);
	if (!_interactive (info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
/**
 * find_builtin - Find a builtin cmd
 * @info: Pointer to the parameter & return info struct.
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1  if builtin found but not successful
 * 2 if builtin signals exit().
 */
int find_builtin(p_info_t *info)
{
	int i, built_in_ret = -1;
	builtin_tbl builtintbl[] = {
		{"exit", _myexit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", change_directory},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - Find a command in PATH.
 * @info: Pointer to parameter & return info struct.
 * Return: void
 */
void find_cmd(p_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((_interactive (info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			perror_(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - Fork a child process to execute a cmd
 * @info: Pointer to parameter & return info struct.
 */
void fork_cmd(p_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_p_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				perror_(info, "Permission denied\n");
		}
	}
}
