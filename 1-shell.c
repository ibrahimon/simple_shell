#include "shell.h"

/**
 *  parse_command - determines the type of the command
 *  @command: the command
 *  Return: constant representing the type of the command
 */

int parse_command(char *command)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;
	
	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (INTERNAL_CMD);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (EXTERNAL_CMD);
	}
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}
	return (INVALID_COMMAND);
}



/**
 * ctrl_C - activate ctrl c
 * @signum: the signal number
 * Return: void
 */

void ctrl_C(int signum)
{
	if (signum == SIGINT)
		print("\n ($) ", STDIN_FILENO);
}

/**
 * _getline - takes input from the user
 *
 * Return: the string read
 */



char *_getline(void)
{
	int bufSize = INPUT_BUF, no_read, position = 0;
	char *buffer = malloc(bufSize * sizeof(char));
	char c;

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !no_read)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				print("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !no_read)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufSize)
		{
			bufSize += INPUT_BUF;
			buffer = _realloc(buffer, INPUT_BUF, bufSize);
			if (!buffer)
			{
				perror("Failed to re-allocate a space in the memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int is_delimeter(const char *delimeters, char c);

/**
 * tokenize - split a string
 * @str: string to split
 * @delim: charcter to split str
 * Return: pointer to new or NULL
 */

char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !(*str))
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);
	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';
		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);

}

/**
 * is_delimeter - check if a character is in delimeter
 * @delimeters: pointer to delimeters
 * @c: character to check
 * Return: 1 for true 0 for false
 */

int is_delimeter(const char *delimeters, char c)
{
	int i = 0;

	if (!delimeters)
		return (0);
	while (delimeters[i])
	{
		if (delimeters[i] == c)
			return (1);
		i++;
	}
	return (0);

}

/**
 * shell_execute - executes a shell
 * @command: the command
 * @cmd_type: command type
 * Return: void
 */

void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);
	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
		if (command_type == PATH_COMMAND)
		{
			if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
			{
				perror(_getenv("PWD"));
				exit(2);
			}
		}
		if (command_type == INTERNAL_COMMAND)
		{
			func = get_func(tokenized_command[0]);
			func(tokenized_command);
		}
		if (command_type == INVALID_COMMAND)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: ", STDERR_FILENO);
			print(tokenized_command[0], STDERR_FILENO);
			print(": not found\n", STDERR_FILENO);
			status = 127;
		}
}

/**
 * check_command - check the command
 * @command: the command
 * Return: inteager
 */

int check_command(char *command)
{
	int i = 0;
	char *int_cmd[] = {"exit", "cd", "env", NULL};

	while (command[i])
	{
		if (command[i] == '/')
			return (EXTERNAL_CMD);
		i++;
	}
	i = 0;
	while (int_cmd[i] != NULL)
	{
		if (_strcmp(command, int_cmd[i]) == 0)
			return (INTERNAL_CMD);
		i++;
	}
	return (INVALID_CMD);
}

/**
 * execute - execute a command
 * @commands: the commands
 * @cmd_type: cmd_type
 * Return: void
 */

void execute(char **commands, int cmd_type)
{
	void (*func)(char **command);

	switch (cmd_type)
	{
		case EXTERNAL_CMD:
			{
				if (execve(commands[0], commands, NULL) == -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(commands[0]);
				func(commands);
				break;
			}
		case PATH_CMD:
			break;
		case INVALID_CMD:
			break;
	}
}
