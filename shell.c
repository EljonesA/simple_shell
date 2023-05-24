#include "shell.h"

void prompt(char *av[], char **env)
{
	int i, status;
	pid_t child_pid;
	char *argv[MAX_ARGS], *token;
	size_t input_size = 0;
	int new_result;
	char *input = NULL;

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

		child_pid = fork();
		argv[0] = input;
		if (child_pid == -1)
		{
			printf("failed fork\n");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			i = 0;
			token = strtok(input, " ");
			while (token != NULL && i < MAX_ARGS - 1)
			{
				argv[i] = token;
				i++;
				token = strtok(NULL, " ");
			}
			argv[i] = NULL;
			if (execve(argv[0], argv, env) == -1)
				printf("%s : failed if cmd fails\n", av[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	free(input);

    return;
}
