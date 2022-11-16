#include "shell.h"

/**
 * env - prints environ command
 * @command: the command
 * Return: void
 */

void env(char **command __attribute__((unused)))
{
	int i = 0;

	while (environ[i])
	{
		print(environ[i++], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the sell
 * @command: the command
 * Return: void
 */

void quit(char **command)
{
	(void) command;
}

/**
 * ch_dir - ch_dir
 * @command: the command
 * Return: void
 */

void ch_dir(char **command)

{
	(void) command;
}
