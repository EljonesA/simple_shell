/**
 * _strcpy - copies a string
 * @dest: pointer to destination string.
 * @src: pointer to source string.
 * Return: resulting copied string.
 */
char *_strcpy(char *dest, char *src)
{
	char *dest_ptr = dest;
	/**>>> code<<<**/
	while (*src != '\0')
		*dest_ptr++ = *src++;
	*dest_ptr = '\0';
	return (dest);
}
/**
 * _strconcat - concatenates two strings
 * @dest: pointer to destination string.
 * @src: pointer to source string.
 * Return: void.
 */
void _strconcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	*dest++ = '/';
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
/**
 * _atoi - converts a string into an integer
 * @s: string to convert to int.
 * Return: converted integer.
 */
int _atoi(char *s)
{
	int sign = 1;
	int result = 0;
	/**>> space <<**/
	while (*s != '\0')
	{
		if (*s == '-')
			sign = -1;
		else if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');
		s++;
		return (sign * result);
	}
}
/**
 * _free_args - free input
 * @args: argument passed
 */
void _free_args(char **args)
{
	if (args == NULL)
		return;
	for (int i = 0; i < MAX_ARGUMENTS && args[i] != NULL; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
}
