#include "shell.h"

/**
 * _print_error_message - writes error msg to stdout
 * @program_name: name of command
 * @error_message: warning to print
 * Return: void.
 */
void _print_error_message(char *program_name, char *error_message)
{
	size_t program_name_len = _strlen(program_name);
	size_t error_message_len = _strlen(error_message);

	write(STDERR_FILENO, program_name, program_name_len);
	write(STDERR_FILENO, error_message, error_message_len);
}

/**
 * _contains_only_spaces - handles space command
 * @input: user input
 * Return: 0(input is space), 1(else).
 */
int _contains_only_spaces(char *input)
{
	size_t i;

	for (i = 0; i < _strlen(input); i++)
	{
		if (input[i] != ' ')
			return (0);
	}
	return (1);
}

/**
 * _free_args - free input
 * @args: argument passed
 * Return: void.
 */
void _free_args(char **args)
{
	int i;

	if (args == NULL)
		return;
	for (i = 0; i < MAX_ARGUMENTS && args[i] != NULL; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
}

