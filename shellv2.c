#include "shell.h"

void prompt(char **ac, char **env)
{
	char *input = NULL;
	size_t input_size = 0;
	pid_t pid;
	int new_result, i;
	char *args[256], *token;
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
			printf("failed fork\n");
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

			execve(args[0], args, env);

			printf("%s: Not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else 
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}
	free(input);

}
int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);
	return (0);
}
