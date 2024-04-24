/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:51:06 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/09/13 18:03:34 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	//char	*s;
	t_data elems;
	pid_t	pid;
	//char	**elems.args;
	char	*cwd;
	int		num;
	int		i;

	while (1)
	{
		elems.s = readline("Minishell >> ");
		getcwd(cwd, sizeof(cwd));
		elems.args = ft_split(elems.s, ' ');
		num = array_size(elems.args);
		elems.args[num + 1] = NULL;
		pid = fork();
		if (strcmp(elems.args[0], "cd") == 0)
		{
			if (elems.args[1] == NULL || strcmp(elems.args[1], "~") == 0)
				chdir("/home/c0mpl3x");
			else
				i = chdir(elems.args[1]);
			if (i == -1)
				perror("error");
		}
		else if (strcmp(elems.s, "pwd") == 0)
			printf("%s", cwd);
		if (pid == -1)
			return (-1);
		else if (pid == 0 && (strcmp(elems.args[0], "cd") != 0))
		{
			execute_command(elems.args[0], elems.args);
		}
		else
			wait (NULL);
	}
	return (0);
}
