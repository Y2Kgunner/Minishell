/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:24:22 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/11/02 23:46:48 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	path_handler(t_data *ptr)
{
	char	*temp;

	ptr->path = ft_strdup(ptr->split_arv[0]);
	temp = ft_strtrim(ptr->split_arv[0], "./");
	if (ptr->split_arv[0][0] == '.')
	{
		free(ptr->split_arv[0]);
		ptr->split_arv[0] = ft_strdup(temp);
	}
	free(temp);
}

static void	ft_execve(t_data *ptr)
{
	ptr->env = convert_to_arr(ptr->lst_export);
	if (execve(ptr->path, ptr->split_arv, ptr->env) == -1)
	{	
		perror("Error");
		ft_free_externals(ptr);
		exit (123);
	}
}

int	ft_externals(t_data *ptr)
{
	if (ptr->split_arv[0][0] == '.' || ptr->split_arv[0][0] == '/')
		path_handler(ptr);
	else if (search_list(ptr->lst_var, "PATH") == 0 || check_path(ptr) == 1)
	{
		printf("Minishell: %s: No such file or directory\n", ptr->arv[0]);
		return (127);
	}
	ptr->pid = fork();
	if (ptr->pid == -1)
		return (-1);
	if (ptr->pid == 0)
		ft_execve(ptr);
	free(ptr->path);
	if (ptr->split_arv)
	{	
		free_array(ptr->split_arv);
		ptr->split_arv = NULL;
	}
	sig_count(1);
	wait(NULL);
	sig_count(2);
	return (0);
}
