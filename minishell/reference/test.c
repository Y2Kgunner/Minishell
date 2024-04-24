#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include "libft.h"

int main (int argc, char **argv, char **envp)
{
	char	*s;
	char	cwd[256];
	int		i;
	char *arv[] = {"/bin/echo", "-n", NULL};
	pid_t	pid;
	int	j = 0;

	(void) argc;
	(void) argv;
	while (1)
	{
		s = readline("Minishell >");
		printf("%s\n", s);
		getcwd(cwd, sizeof(cwd));
		if (strlen (s) > 0)
			add_history(s);
		if (strcmp(s, "env") == 0)
		{
			while (envp[j] != NULL)
				printf("%s\n", envp[j++]);
		}
		if (strcmp(s, "pwd") == 0)
			printf("%s\n", cwd);
		if (strcmp(s, "cd ..") == 0)
		{
			i = chdir("..");
			if (i == -1)
				perror("Error");
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (strcmp(s, "echo") == 0)
				if (execve(arv[0], arv, envp) == -1)
					perror("Error");
		}
		else 
			wait(NULL);	
		if (strcmp(s, "env") == 0)
			printf("%s\n", getenv("HOME"));
	}
}