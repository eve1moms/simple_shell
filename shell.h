#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define SIZE_BUF_WRITE 1024
#define SIZE_BUF_READ 1024
#define FLUSH_BUF -1

/* for command chaining */
#define _NORMAL_CMD 0
#define _OR_CMD		1
#define _AND_CMD		2
#define _CHAIN_CMD	3

/* for convert_num_to_str() */
#define CONVERT_LW	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define _STRTOP 0

#define FILE_HIST	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;


/**
 * struct linked_list - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct linked_list
{
	int num;
	char *str;
	struct linked_list *next;
} list_t;

/**
 * struct p_info - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} p_info_t;

#define P_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(p_info_t *);
} builtin_tbl;


/* toem_shloop.c */
int _shell(p_info_t *, char **);
int find_builtin(p_info_t *);
void find_cmd(p_info_t *);
void fork_cmd(p_info_t *);

/* toem_parser.c */
int is_cmd(p_info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(p_info_t *, char *, char *);

/* loopshell.c */
int loopshell(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **_strtop(char *, char *);
char **_strtop2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _interactive(p_info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void perror_(p_info_t *, char *);
int print_d(int, int);
char *num_to_str(long int, int, int);
void delete_comments(char *);

/* toem_builtin.c */
int _myexit(p_info_t *);
int change_directory(p_info_t *);
int my_help(p_info_t *);

/* toem_builtin1.c */
int my_history(p_info_t *);
int my_alias(p_info_t *);

/*toem_getline.c */
ssize_t get_input(p_info_t *);
int _getline(p_info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_p_info(p_info_t *);
void set_p_info(p_info_t *, char **);
void free_p_info(p_info_t *, int);

/* toem_environ.c */
char *_getenv(p_info_t *, const char *);
int my_env(p_info_t *);
int _mysetenv(p_info_t *);
int _myunsetenv(p_info_t *);
int populate_env_list(p_info_t *);

/* toem_getenv.c */
char **get_environ(p_info_t *);
int _unsetenv(p_info_t *, char *);
int _setenv(p_info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(p_info_t *info);
int write_history(p_info_t *info);
int read_history(p_info_t *info);
int build_history_list(p_info_t *info, char *buf, int linecount);
int renumber_history(p_info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(p_info_t *, char *, size_t *);
void check_chain(p_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(p_info_t *);
int replace_vars(p_info_t *);
int replace_string(char **, char *);

#endif
