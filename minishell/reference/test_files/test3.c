/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lara.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:56:29 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/08/31 13:03:17 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void	external_commands(char **args)
{
	pid_t	pid;
	char	*path;
	char	*env[] = {"PATH=/bin", "USER=me", NULL};
	char 	*s;

	*args = readline("MINISHELL>> ");
	path = strcat("/bin/", *args);
	execve(path, args, env);
}

int	main(void)
{
	char	*s;
	char	*path;
	char	cwd[256];
	char	*args[100];
	pid_t	pid;
	//char *env_args[] = { "PATH=/bin", "USER=me", NULL };

	pid = fork();
	while (1)
	{	
		//s = readline("\nMINISHELL >> ");
		// path = strcat(s, "/bin/");
		// execve(path, args, env_args);
		// getcwd(cwd, sizeof(cwd));
		// if (strcmp(s, "pwd") == 0)
		// 	printf("%s", cwd);
		external_commands(args);

	}
	free (s);
	return (0);
}