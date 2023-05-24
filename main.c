#include "shell.h"

int main(void)
{
         setenv("PATH", "/usr/bin:/bin:/usr/local/bin", 1);
        prompt(NULL, environ);
        return (0);
}
