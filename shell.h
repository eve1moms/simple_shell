#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

/* for command chaining */
#define _NORMAL_CMD 0
#define _OR_CMD         1
#define _AND_CMD                2
#define _CHAIN_CMD      3

/* for read/write buffers */
#define SIZE_BUF_WRITE 1024
#define SIZE_BUF_READ 1024
#define FLUSH_BUF -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define _STRTOP 0

#define FILE_HIST       ".simple_shell_history"
#define HISTORY_MAX     4096

/* for convert_num_to_str() */
#define CONVERT_LW	1
#define CONVERT_UNSIGNED	2


extern char **environ;


/**
 * struct linked_list - This function is singly linked list
 * @str: this is the sring
 * @num: this is the NUmber field
 * @next: this is the  points 2 the NEXT node
 */
typedef struct linked_list
{
	int num;
	char *str;
	struct linked_list *next;
} list_t;

/**
 * struct p_info - This function contains PSEUDO-arguements 2 pass into a funct
 *  thus allowing UNIFORM prototype for funct ptr struct
 * @argc: this is the argument count
 * @path: this is a string path for the cmd
 * @arg: a string generated from getline containing arguements
 * @fname: this is the program filename
 * @environ: this is a  custom MOdified cpy of environ 4rm LL env
 * @alias: this is tthe alias NODE
 * @line_count this is the error COUNT
 * @env: this is the linked list copy of ENVIROn
 * @readfd: this is the file descriptor from which READAD file input
 * @cmd_buf: this is the adress of PTR 2 cmd_buf if chaining
 * @histcount: this is the hist line no
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @argv:This is the arr of str generated from args
 * @status: this is the return statues of LAST EXEC'S
 * @linecount_flag: thas is if it is on count tthis line ofINPUT
 * @env_changed: this is on if the envirin is changes
 * @err_num: the error code for exit()s
 * @history: the history node
 */
typedef struct p_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} p_info_t;

#define P_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - this function containa a buil in str& related func
 * @func: this is the function
 * @type: this is the buillt in cmd flag
 */
typedef struct builtin
{
	char *type;
	int (*func)(p_info_t *);
} builtin_tbl;


/* TOEM_shelloop.c */
int find_builtin(p_info_t *);
void fork_cmd(p_info_t *);
int _shell(p_info_t *, char **);
void find_cmd(p_info_t *);

/* toem_str1.c */
int _putchar(char);
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);

/* toem_str.c */
char *_strcat(char *, char *);
int _strcmp(char *, char *);
int _strlen(char *);
char *starts_with(const char *, const char *);

/* TOEM_io.c */
int _putsfd(char *str, int fd);
int _eputchar(char);
void _eputs(char *);
int _putfd(char c, int fd);


/* toem_cmd.c */
char *dup_chars(char *, int, int);
int is_cmd(p_info_t *, char *);
char *find_path(p_info_t *, char *, char *);

/* lopshell.c */
int loopshell(char **);

/* toem_err1.c */
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _putfd(char c, int fd);

/* TOEM_memset.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_utility.c */
int _interactive(p_info_t *);
int _atoi(char *);
int is_delim(char, char *);
int _isalpha(int);

/* toem_cp_str.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_io1.c */
void perror_(p_info_t *, char *);
char *num_to_str(long int, int, int);
int _erratoi(char *);
int print_d(int, int);
void delete_comments(char *);


/* toem_builtin1.c */
int my_history(p_info_t *);
int my_alias(p_info_t *);

/* toem_builtin_shell.c */
int change_directory(p_info_t *);
int _myexit(p_info_t *);
int my_help(p_info_t *);

/* toem_ls1.c */
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

/* toem_ls.c */
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);


/* toem_splits_str.c */
char **_strtop2(char *, char);
char **_strtop(char *, char *);


/* toem_mem.c */
int bfree(void **);

/* toem_environ_shell.c */
int populate_env_list(p_info_t *);
int _mysetenv(p_info_t *);
int my_env(p_info_t *);
int _myunsetenv(p_info_t *);
char *_getenv(p_info_t *, const char *);

/*toem_input_buf.c */
int _getline(p_info_t *, char **, size_t *);
ssize_t get_input(p_info_t *);
void sigintHandler(int);

/* toem_info.c */
void set_p_info(p_info_t *, char **);
void clear_p_info(p_info_t *);
void free_p_info(p_info_t *, int);


/* toem_hist_io.c */
int write_history(p_info_t *info);
int build_history_list(p_info_t *info, char *buf, int linecount);
char *get_history_file(p_info_t *info);
int read_history(p_info_t *info);
int renumber_history(p_info_t *info);

/* toem_env.c */
char **get_environ(p_info_t *);
int _setenv(p_info_t *, char *, char *);
int _unsetenv(p_info_t *, char *);


/* toem_delim_test.c */
void check_chain(p_info_t *, char *, size_t *, size_t, size_t);
int replace_vars(p_info_t *);
int is_chain(p_info_t *, char *, size_t *);
int replace_alias(p_info_t *);
int replace_string(char **, char *);


#endif
