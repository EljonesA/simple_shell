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

/**
 * _itoa - converts an integer to a string
 * @value: input integer value
 * @str: stores converted str
 * Return: length of resulting string.
 */
int _itoa(int value, char *str)
{
	int i = 0;
	int length, j;
	bool is_negative = false;

	if (value < 0) /* handle -ve numbers */
	{
		is_negative = true;
		value = -value;
	}
	do { /* convert @digit to char in reverse order */
		str[i++] = value % 10 + '0';
		value /= 10;
	} while (value != 0);

	if (is_negative) /* add - sign if the number was negative */
		str[i++] = '-';

	/* reverse the string */
	length = i;
	for (j = 0; j < length / 2; j++)
	{
		char temp = str[j];

		str[j] = str[length - j - 1];
		str[length - j - 1] = temp;
	}
	str[i] = '\0';

	return (length);
}

ssize_t _getline(char **line_ptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t buf_size;
	static ssize_t buf_pos;
	size_t line_len;
	char *line;
	size_t line_capacity;
	char current_char;

	if (buf_pos >= buf_size)
	{
		buf_size = read(fd, buffer, BUFFER_SIZE);
		buf_pos = 0;

		if (buf_size <= 0)
			return (buf_size); /* EOF/error */
	}

	line_len = 0;
	line = *line_ptr;
	line_capacity = *n;

	while (buf_pos < buf_size)
	{
		if (line_len >= line_capacity - 1)
			return (-1); /* line len exceeds buffer capacity */
		current_char = buffer[buf_pos++];
		line[line_len++] = current_char;

		if (current_char == '\n')
		{
			line[line_len] = '\0';
			return (line_len);
		}
	}
	return (line_len);
}
