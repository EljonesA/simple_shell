#include <stddef.h>

size_t _strcspn(const char *str, const char *delimiters)
{
    const char *p;
    const char *s;
    size_t count = 0;

    for (s = str; *s != '\0'; s++)
    {
        for (p = delimiters; *p != '\0'; p++)
        {
            if (*s == *p)
            {
                return count;
            }
        }
        count++;
    }

    return count;
}

