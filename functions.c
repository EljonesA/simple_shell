#include "shell.h"

/**
 * _remove_newline_char - replace newline char with null char
 * @s: user input.
 * Return: void.
 */
void _remove_newline_char(char *s)
{
	size_t len = _strlen(s);

	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

/**
 * _handle_Command_line_arguments - tokenize user input
 * @input: user input.
 * Return: a pointer to the whole arguments list.
 */
char **_handle_Command_line_arguments(char *input)
{
	char *token;
	int args_count = 0;
	char **args = NULL;

	if (input == NULL)
		return (NULL);
	args = malloc((MAX_ARGUMENTS + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " ");
	while (token != NULL && args_count < MAX_ARGUMENTS)
	{
		args[args_count] = malloc(_strlen(token) + 1);
		if (args[args_count] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		_strcpy(args[args_count], token);
		token = strtok(NULL, " ");
		args_count++;
	}
	args[args_count] = NULL;
	return (args);
}

/**
 * _execute_command - executes user command
 * @args: pointer to user command + arguments
 * @env: pointer to environment variables
 * Return: child PID.
 */
pid_t _execute_command(char **args, char **env)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(args[0], args, env) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (child_pid);
}

/**
 * _check_PATH - checks if user input is in PATH
 * @args: pointer to user command + arguments
 * @env: pointer to environmnet variables
 * Return: void.
 */
void _check_PATH(char **args, char *env[])
{
	char *path = getenv("PATH");
	char *path_copy = malloc(_strlen(path) + 1);
	char *path_token;
	
	if (path_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strcpy(path_copy, path); /* make copy of path */

	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		char command_path[1024];

		command_path[0] = '\0'; /* initialize with null char */
		_strconcat(command_path, path_token);
		_strconcat(command_path, "/");
		_strconcat(command_path, args[0]);

		if (access(command_path, F_OK) == 0)
		{
			/* command exists, execute it */
			execve(command_path, args, env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		path_token = strtok(NULL, ":");
	}
	write(STDOUT_FILENO, "No such file or directory\n", 26);
	exit(EXIT_FAILURE);
}

/**
 * _execute_PATH - if user input is in PATH, executes it in shell function
 * @args: pointer to user command + arguments
 * @env: pointer to environment variables
 * Return: void.
 */
void _execute_PATH(char **args, char **env)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		_check_PATH(args, env); /* check executables in PATH */
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}



