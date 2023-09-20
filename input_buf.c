#include "shell.h"
/**
 * input_buf -this functioon reads INPUT and BUF chained commads
 * @buf: this is the adress of the buf
 * @info: this is the  Parameter 2 strct containing  the shell info
 * @len: this is the adress to the length var
 * Return: the no of bytes READ
 */
ssize_t input_buf(p_info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			delete_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input - Thhis function Gets a line of input withoutnewline char
 * @info: this is a Parameter strct having shell info
 * Return:the no of bytes read
 */
ssize_t get_input(p_info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(FLUSH_BUF);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = _NORMAL_CMD;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
/**
 * read_buf - this function Reads buf from A fd
 * @buf: this is the buf to store the read data.
 * @info: this is the Parameter Strct having shell info
 * @i:  this is the size of the buf
 * Return: the no if BYtes it has read
 */
ssize_t read_buf(p_info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, SIZE_BUF_WRITE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * _getline - Thisfunction Gets  next line INPUT from STDIN.
 * @ptr: this is the adress of the pointer to the buf, prelocated or null
 * @info: this is the Parameter strct having the shell info
 * @length: this is the size of PREallocated ptr buf if not NULL.
 * Return: REturns no of BYtes read
 */
int _getline(p_info_t *info, char **ptr, size_t *length)
{
	static char buf[SIZE_BUF_READ];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - this function Blocks Ctrl-C signals
 * @sig_num: This is the signal no
 * Return: returns void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUF);
}
