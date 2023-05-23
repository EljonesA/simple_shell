/**
 * _strcmp - compares two strings
 * @s1: pointer to first string.
 * @s2: pointer to second string.
 * Return: 0(strings match), 1(strings do not match).
 */
int _strcmp(char *s1, char *s2)
{
    unsigned int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }

    if (s1[i] != s2[i])
        return (1);

    return (0);
}

/**
 * _strlen - computes length of a string
 * @s: string to get length
 * Return: length of the string.
 */
size_t _strlen(char *s)
{
    size_t len = 0;

    while (s[len] != '\0')
        len++;
    return (len);
}

/**
 * _strcpy - copies a string
 * @dest: pointer to destination string.
 * @src: pointer to source string.
 * Return: resulting copied string.
 */
char *_strcpy(char *dest, char *src)
{
    char *dest_ptr = dest;

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

OB
/**
 * _atoi - converts a string into an integer
 * @s: string to convert to int.
 * Return: converted integer.
 */
int _atoi(char *s)
{
    int sign = 1; /* stores sign of the number */
    int result = 0; /* stores converted int result */

    while (*s != '\0')
    {
        if (*s == '-') /* check if current char is (-) sign */
            sign = -1;
        else if (*s >= '0' && *s <= '9')
            result = result * 10 + (*s - '0');

        s++;
    }

    return (sign * result); /* apply appropriate +/- value */
}
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
