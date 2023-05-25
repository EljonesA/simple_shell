#include "shell.h"

/**
 * shell - the shell function
 * description: handles command-line arguements, exit, env, PATH
 * setenv, unsetenv, cd
 * Return: 0(always success).
 */
int shell(void)
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t nread;
	/*pid_t child_pid;*/
	int status;
	char **args;
	char *env[] = {NULL}; /* empty environment variable array */

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		if (isatty(STDIN_FILENO)) /* interactive vs non-interactive */
		{
			nread = getline(&input, &input_len, stdin);
			if (nread == -1)
			{
				write(STDOUT_FILENO, "\nEOF ecountered\n", 30);
				break;
			}
		}
		else
		{
			nread = getline(&input, &input_len, stdin);
			if (nread == -1)
				break;
		}

		if (input[0] == '\n') /* handle empty command */
		{
			free(input);
			input = NULL;
			input_len = 0;
			continue;
		}
		/* remove newline char at end of input */
		_remove_newline_char(input);

		/* chck if input contains only spaces */
		if (_contains_only_spaces(input))
		{
			free(input);
			input = NULL;
			input_len = 0;
			continue;
		}
		/* handle command line arguments */
		args = _handle_Command_line_arguments(input);

		if (access(args[0], X_OK) == 0) /* check current dir */
		{
			_execute_command(args, env);
			wait(&status);
		}
		else if (_strcmp(args[0], "/bin/ls") == 0)
		{
			_execute_command(args, env);
			wait(&status);
		}
		else if (_strcmp(input, "exit") == 0) /* handle exit built-in */
		{
			_handle_exit(args, input);
		}
		else if (_strcmp(input, "env") == 0) /* handle env built-in */
		{
			_print_environment_variables();
		}
		else if (_strcmp(args[0], "setenv") == 0) /* handle setenv */
		{
			_setenv_command(args);
		}
		else if (_strcmp(args[0], "unsetenv") == 0) /* unsetenv */
		{
			_unsetenv_command(args);
		}
		else if (_strcmp(args[0], "cd") == 0) /* handle cd built-in */
		{
			_cd_command(args);
		}
		else /* check in PATH for executables */
		{
			_execute_PATH(args, env);
		}

		_free_args(args);
		free(input);
		input = NULL;
		input_len = 0;
	}
	free(input);
	return (0);
}

