#include "shell.h"
/**
 * is_cmd - the function checks if a file is an executable cmdi
 * @path: pathew ay to the file
 * @info: this is the pinter to file
 * Return: if ifle is an execytable command return 1 else 0
 */
int is_cmd(p_info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - this duplicated the chars toa given string
 * @stop: stopping point(index) for the characters to duplicate
 * @start: strsting point(index) for char to duplicate.
 * @pathstr:  PATH string.
 * Return: Apointer to a buf containg the duplicate chars
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = '\0';
	return (buf);
}
/**
 * find_path - this locates a specified cmd to the string
 * @cmd: the command to locate
 * @pathstr: this is the pathway to the string
 * @info: this is justthe pointer to e info structure
 * Return: a pathway to the cmd else NULL
 */
char *find_path(p_info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
