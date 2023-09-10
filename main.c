#include "shell.h"
/**
 * main -This is the main entry point
 * @av: this is the argument vector
 * @ac: this is the argument count
 * Return: if uscessfulreturn 0 else 1
 */
int main(int ac, char **av)
{
	p_info_t info[] = { P_INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(FLUSH_BUF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	_shell(info, av);
	return (EXIT_SUCCESS);
}
