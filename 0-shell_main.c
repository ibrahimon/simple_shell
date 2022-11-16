#include "shell.h"

/**
 * main - shell process
 * @argc: number of arguments
 * @argv: a pointer to a pointer to input command
 * Return: command excution
 */

int main(int argc __attribute__((unused)), char **argv)

{
	char *line;
	char **args;
	int cmd_type;
	(void) argv;

	signal(SIGINT, ctrl_C);

	while (1)
	{
		print(" ($) ", STDOUT_FILENO);
		line = _getline();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				break;
		}
		args = tokenize(line, DELIMT);
		cmd_type = check_command(args[0]);
		shell_execute(args, cmd_type);
	}
	return (1);
