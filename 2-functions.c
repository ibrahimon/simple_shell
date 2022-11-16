#include "shell.h"

/**
 * print - prints variables
 * @var: the variable
 * @fd: inteager
 * Return: inteager
 */

int print(char *var, int fd)
{
	return (write(fd, var, _strlen(var)));
}

/**
 * get_func - manages shell
 * @command: the command
 * Return: void
 */

void (*get_func(char *command))(char **)
{
	int i;
	func map[] = {
		{"env", env},
		{"cd", ch_dir},
		{"exit", quit}
	};

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(command, map[i].cmd_name) == 0)
			return (map[i].func);
	}
	return (NULL);
}
