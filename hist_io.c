#include "shell.h"
/**
 * get_history_file - this retrieves thre hist file pathway
 * @info: this is the pointer to the parameter struct
 * Return: the alloctaed strg containing the pathway of hst file
 */
char *get_history_file(p_info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(FILE_HIST) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, FILE_HIST);
	return (buf);
}
/**
 * write_history - this function writes the hist to a file
 * @info: This is the poiter to the parameter struect
 * Return: if sucessful 1 else 0
 */
int write_history(p_info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(FLUSH_BUF, fd);
	close(fd);
	return (1);
}
/**
 * read_history - this function READS hist from a file
 * @info: This is the pointer to the parameter file
 * Return: on success retuen no of hist file else 0
 */
int read_history(p_info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HISTORY_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - Function adds an entry to the hit linked list
 * @buf: this is the buf containing the hitory entry
 * @info: the struct containingpotential args
 * @linecount: this is the histiry line count
 * Return: 0.
 */
int build_history_list(p_info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - this function renumber the history linked listed
 * after changes have been made
 * @info: this is the structure containing poyential args
 * Return: THE new histcount.
 */
int renumber_history(p_info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
