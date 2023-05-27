#include "shell.h"

int last_status; /* handle variable replacements */

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
	int i;

	if (input == NULL)
		return (NULL);
	args = malloc((MAX_ARGUMENTS + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	/* initilize memory for args array */
	for (i = 0; i < MAX_ARGUMENTS + 1; i++)
		args[i] = NULL;

	/* comments - ignore everything after # */
	token = strtok(input, "#");

	token = strtok(input, " ");
	while (token != NULL && args_count < MAX_ARGUMENTS)
	{
		args[args_count] = malloc(_strlen(token) + 1);
		if (args[args_count] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		/* handle variable replacement */
		if (_strcmp(token, "$?") == 0)
		{
			char exit_status_str[4];
			int exit_status_len = _itoa(WEXITSTATUS(last_status),
					exit_status_str);
			write(STDOUT_FILENO, exit_status_str, exit_status_len);
		}
		else if (_strcmp(token, "$$") == 0)
		{
			char pid_str[10];
			int pid_len = _itoa(getpid(), pid_str);
			write(STDOUT_FILENO, pid_str, pid_len);
		}
		else
			_strcpy(args[args_count], token);
		token = strtok(NULL, " ");
		args_count++;
	}
	args[args_count] = NULL;

	/* free memory if args_count is less than MAX_ARGUMENTS */
	for (i = args_count; i < MAX_ARGUMENTS; i++)
	{
		free(args[i]);
	}
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
	else
		wait(&last_status); /* save exit status */
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
	char *error_message;

	if (path_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strcpy(path_copy, path); /* make copy of path */

	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		size_t command_path_len = _strlen(path_token) + _strlen(args[0]
				) + 3;
		char *command_path = malloc(command_path_len);
		if (command_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		command_path[0] = '\0'; /* initialize with null char */
		_strconcat(command_path, path_token);
		_strconcat(command_path, "/");
		_strconcat(command_path, args[0]);

		if (access(command_path, F_OK) == 0)
		{
			/* command exists, execute it */
			execve(command_path, args, env);
			perror("execve");
			free(path_copy); /* free allocated mem before exit */
			free(command_path);
			exit(EXIT_FAILURE);
		}
		free(command_path);
		path_token = strtok(NULL, ":");
	}
	error_message = ": not found\n";

	_print_error_message(args[0], error_message);

	free(path_copy); /* free allocated memory before exit */
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

