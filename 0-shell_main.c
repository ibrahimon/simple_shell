#include "shell.h"

/**
 * main - shell process
 * @argc: number of arguments
 * @argv: a pointer to a pointer to input command
 * Return: command excution
 */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))

{
	char **commands = NULL;
	char *line = NULL;
	int status = 0;
	char **current_command = NULL;
	int i, type_command = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_C);
	while (1)
	{
		non_inactive();
		print(" $ ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
		remove_newline(line);
		remove_comment(line);
		commands = tokenize(line, ";");
		for (i = 0; commands[i] != NULL; i++)
		{
			current_command = tokenize(commands[i], " ");
			if (current_command[0] == NULL)
			{
				free(current_command);
				break;
			}
			type_command = parse_command(current_command[0]);
			initial(current_command, type_command);
			free(current_command);
		}
		free(commands);
	}
	free(line);

	return (status);
}
