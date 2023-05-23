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
