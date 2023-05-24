#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 10
extern char **environ;
void prompt(char *av[], char **env);
size_t _strcspn(const char *str, const char *delimiters);
/* >>>> support_functions.c <<<< */
int _strcmp(char *s1, char *s2);
size_t _strlen(char *s);
char *_strcpy(char *dest, char *src);
void _strconcat(char *dest, char *src);
int _atoi(char *s);

/* >>>> functions.c <<<< */
void _remove_newline_char(char *s);
char **_handle_Command_line_arguments(char *input);
pid_t _execute_command(char **args, char **env);
void _check_PATH(char **args, char *env[]);
void _execute_PATH(char **args, char **env);

/* >>>> built-in.c <<<< */
void _print_environment_variables(void);
void _handle_exit(char **args, char *input);
void _setenv_command(char **args);
void _unsetenv_command(char **args);
void _cd_command(char **args);

/* >>>> shell.c <<<< */
int shell(void);
void _free_args(char **args);

#endif
