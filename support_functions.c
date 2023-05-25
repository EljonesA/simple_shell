#include "shell.h"

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
		{
			return (1);
		}
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
 * _strcpy - copies s string
 * @dest: destination to e copied to
 * @src: string to copy
 * Return: resulting string.
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
 * @dest: string to concatenate to
 * @src: source string
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
 * _atoi - converts string to integer
 * @s: input string
 * Return: resulting integer value.
 */
int _atoi(char *s)
{
	int sign = 1; /* stores sign of the number */
	int result = 0; /* stores converted int result */

	while (*s != '\0')
	{
		if (*s == '-')
			sign = -1;
		else if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');

		s++;
	}
	return (sign * result); /* apply appropriate +/- value */
}

