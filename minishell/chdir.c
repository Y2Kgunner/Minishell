/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:56:34 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/11/02 13:40:38 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *ptr)
{
	char	*str;
	char	*s;

	if (search_list(ptr->lst_var, "HOME") != 0)
		s = ft_strdup(search_list(ptr->lst_var, "HOME"));
	else
		s = ft_strdup("/Users/laraelkhoury");
	if (ptr->arv[1] == NULL && search_list(ptr->lst_var, "HOME") == 0)
	{
		printf("Minishell: cd: HOME not set\n");
		return ;
	}
	if (ptr->arv[1] == NULL || ft_strcmp(ptr->arv[1], "~") == 0)
		ptr->i = chdir(s);
	else if (ptr->arv[1][0] == '~')
	{
		str = ft_strjoin(s, (ptr->arv[1] + 1));
		ptr->i = chdir(str);
		free(str);
	}
	else
		ptr->i = chdir(ptr->arv[1]);
	if (ptr->i == -1)
		perror("Error");
	free(s);
}

void	ft_cd_main(t_data *ptr)
{
	if (ft_strcmp(ptr->split_arv[1], "-") == 0)
		chdir(search_list(ptr->lst_envp, "OLDPWD"));
	else
		ft_cd(ptr);
	getcwd(ptr->cwd, sizeof(ptr->cwd));
	change_variable(ptr->lst_envp, "OLDPWD", search_list(ptr->lst_var, "PWD"));
	change_variable(ptr->lst_export, "OLDPWD", \
	search_list(ptr->lst_var, "PWD"));
	change_variable(ptr->lst_var, "OLDPWD", search_list(ptr->lst_var, "PWD"));
	change_variable(ptr->lst_envp, "PWD", ptr->cwd);
	change_variable(ptr->lst_export, "PWD", ptr->cwd);
	change_variable(ptr->lst_var, "PWD", ptr->cwd);
}
