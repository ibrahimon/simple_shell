#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>



/* innitial size of buffer for user input */
#define INPUT_BUF 1000

#define DELIMT " \a\t\r\n"

/* commands */

#define INTERNAL_CMD 1
#define EXTERNAL_CMD 2
#define PATH_CMD 3
#define INVALID_CMD -1

/* Global environ variable */

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

typedef struct internal_func
{
	char *cmd_name;
	void (*func)(char **command);
} func;

/* builtin command */
void env(char **);
void quit(char **);

/* shell utility function */
void ctrl_C(int);
char *_getline(void);
char **tokenize(char *, const char *);
void execute_command(char **tokenized_command, int command_type);
int check_command(char *);
int parse_command(char *);

/* shell helper function */
int print(char *, int);
void (*get_func(char *))(char **);
void remove_comment(char *);

/* shell string functions */
int _strlen(char *);
int _strcmp(char*, char *);
void remove_newline(char *);

/* shell memory management */
void *_realloc(void *, int, int);

/* environment path */
char *_getenv(char *);

extern void non_inactive(void);
extern void initial(char **current_command, int type_command);

#endif
