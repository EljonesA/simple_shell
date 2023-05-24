#include "shell.h"

void prompt(char **ac, char **env)
{
	pid_t pid;
	int new_result, i;
	char *args[256], *token;
	 char command_path[256];
	char *path;
	char *path_token;
	char *input = NULL;
        size_t input_size = 0;
	(void)ac;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		new_result = getline(&input, &input_size, stdin);
		if (new_result == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{
                        free(input);
                        exit(EXIT_SUCCESS);
                }
		pid = fork();
		if (pid == -1)
		{
			printf("Failed to fork\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			i = 0;
			token = strtok(input, " ");
			while (token != NULL)
			{
				args[i] = token;
				i++;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			path = getenv("PATH");
			path_token = strtok(path, ":");

			while (path_token != NULL)
			{
				snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);
				if (access(command_path, X_OK) == 0)
				{
					execve(command_path, args, env);
					printf("Failed to execute command\n");
					exit(EXIT_FAILURE);
				}
				path_token = strtok(NULL, ":");
			}
			printf("Command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}
}

int main(void)
{
         setenv("PATH", "/usr/bin:/bin:/usr/local/bin", 1);
        prompt(NULL, environ);
        return (0);
}
