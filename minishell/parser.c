/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:49:17 by lel-khou          #+#    #+#             */
/*   Updated: 2022/11/02 23:48:25 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **s)
{
	int	i;
	int	j;

	if (!s[1])
	{
		printf("\n");
		return ;
	}
	j = ft_strcmp(s[1], "-n");
	if (j == 0)
		i = 3;
	else
		i = 1;
	while (i < ft_sizeofarray(s))
	{
		printf("%s", s[i]);
		i++;
	}
	if (j != 0)
		printf("\n");
}

void	print_env(t_data *ptr)
{
	t_env	*temp;

	temp = ptr->lst_envp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->var[0], "SHLVL") == 0)
		{
			if (ft_strcmp(temp->var[1], "0") == 0)
			{
				printf("%s=\n", temp->var[0]);
				temp = temp->next;
			}
		}
		printf("%s=%s\n", temp->var[0], temp->var[1]);
		temp = temp->next;
	}
}

static void	ft_parser(t_data *ptr)
{
	getcwd(ptr->cwd, sizeof(ptr->cwd));
	if (ft_strcmp(ptr->arv[0], "pwd") == 0)
		printf("%s\n", ptr->cwd);
	else if (ft_strcmp(ptr->arv[0], "cd") == 0)
		ft_cd_main(ptr);
	else if (ft_strcmp(ptr->arv[0], "env") == 0)
		print_env(ptr);
	else if (ft_strcmp(ptr->arv[0], "echo") == 0)
		ft_echo(ptr->arv);
	else if (ft_strcmp(ptr->arv[0], "exit") == 0)
	{
		ft_free_exit(ptr);
		exit (0);
	}
	else if (ft_strcmp(ptr->arv[0], "unset") == 0)
		ft_unset(ptr);
	else if (ft_strcmp(ptr->arv[0], "export") == 0)
		ft_export(ptr);
	else if (ft_strchr(ptr->arv[0], '=') != 0)
		add_variable(ptr);
	else
		ft_externals(ptr);
}

int	single_parse(t_data *ptr)
{
	if (ptr->arv[0] == NULL)
		return (0);
	if (ptr->split_arv[0] == NULL)
	{
		printf("Minishell: %s: No such file or directory\n", ptr->arv[0]);
		return (0);
	}
	ft_parser(ptr);
	return (0);
}
