#include "shell.h"

/**
 * _print_environment_variables - prints environment variables
 * Return: void.
 */
void _print_environment_variables(void)
{
	extern char **environ;
	int i = 0;
	char **env = environ;

	if (env == NULL)
		return;

	while (env[i] != NULL)
	{
		size_t len = _strlen(env[i]);

		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * _handle_exit - handles exit built-in
 * @args: pointer to user command + arguments
 * @input: user input
 * Return: void.
 */
void _handle_exit(char **args, char *input)
{
	if (args[1] != NULL) /* handle exit arguments */
	{
		int status = _atoi(args[1]);

		_free_args(args);
		free(input);
		exit(status);
	}
	_free_args(args);
	free(input);
	exit(EXIT_SUCCESS);
}

/**
 * _setenv_command - handles setenv built-in
 * @args: pointer to user command + argumnets
 * Return: void.
 */
void _setenv_command(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		perror("Usage: setenv VARIABLE VALUE");
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("Failed to set environment variable");
		return;
	}
}

/**
 * _unsetenv_command - handles unsetenv built-in
 * @args: pointer to user command + arguments
 * Return: void.
 */
void _unsetenv_command(char **args)
{
	if (args[1] == NULL)
	{
		perror("Usage: unsetenv VARIABLE");
		return;
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv failed");
		return;
	}
}

/**
 * _cd_command - handles cd built-in
 * @args: pointer to user command + arguments
 * Return: void.
 */
void _cd_command(char **args)
{
	char *path = args[1];
	char cwd[1024];

	if (path == NULL) /* cd without arguments, change to $HOME */
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			perror("HOME environment variable not set");
			return;
		}
	}
	else if (_strcmp(path, "-") == 0) /* cd -, change to previous dir */
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			perror("OLDPWD environment variable not set");
			return;
		}
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL) /* store fullpath of cwd */
	{
		perror("getcwd");
		return;
	}

	if (chdir(path) != 0) /* change to dir specified in path */
	{
		perror("chdir");
		return;
	}

	/* update PWD environment variable */
	if (setenv("PWD", getcwd(cwd, sizeof(cwd)), 1) != 0)
	{
		perror("setenv");
		return;
	}
}
