/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:45:27 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/11/02 23:48:36 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pid1(t_data *ptr, int i)
{
	int	j;

	j = 0;
	free(ptr->s);
	ptr->s = ft_strdup(ptr->split_pr[ptr->k]);
	ptr->s = var_expander(ptr, ptr->s);
	ptr->arv = ft_split_single(ptr);
	ft_remove_space(ptr);
	while (j < ptr->pcount)
	{
		close(ptr->fd[j][0]);
		if (j != 0)
			close(ptr->fd[j][1]);
		j++;
	}
	ft_redirections(ptr, i);
	single_parse(ptr);
	ft_free_pipes(ptr);
	exit (0);
}

static void	ft_pid2(t_data *ptr, int i)
{
	int	j;

	j = 0;
	free(ptr->s);
	ptr->s = ft_strdup(ptr->split_pr[ptr->k]);
	ptr->s = var_expander(ptr, ptr->s);
	ptr->arv = ft_split_single(ptr);
	ft_remove_space(ptr);
	while (j < ptr->pcount)
	{
		if (j != i - 1)
			close(ptr->fd[j][0]);
		if (j != i)
			close(ptr->fd[j][1]);
		j++;
	}
	dup2(ptr->fd[i - 1][0], STDIN_FILENO);
	ft_redirections(ptr, i);
	close(ptr->fd[i - 1][0]);
	single_parse(ptr);
	ft_free_pipes(ptr);
	exit (0);
}

static void	ft_pid3(t_data *ptr, int i)
{
	int	j;

	j = 0;
	free(ptr->s);
	ptr->s = ft_strdup(ptr->split_pr[ptr->k]);
	ptr->s = var_expander(ptr, ptr->s);
	ptr->arv = ft_split_single(ptr);
	ft_remove_space(ptr);
	while (j < ptr->pcount)
	{
		close(ptr->fd[j][1]);
		if (j != i - 1)
			close(ptr->fd[j][0]);
		j++;
	}
	dup2(ptr->fd[i - 1][0], STDIN_FILENO);
	ft_redirections(ptr, i);
	close(ptr->fd[i - 1][0]);
	single_parse(ptr);
	ft_free_pipes(ptr);
	exit (0);
}

static	void	create_pipes(t_data *ptr)
{
	int	i;

	i = 0;
	ptr->fd = malloc(sizeof(int *) * ptr->pcount);
	while (i < ptr->pcount)
	{
		ptr->fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < ptr->pcount)
	{
		if (pipe(ptr->fd[i]) == -1)
			return ;
		i++;
	}
}

void	ft_pipe(t_data *ptr)
{
	int	i;

	i = -1;
	split_pipes_redirections(ptr);
	create_pipes(ptr);
	while (i < ptr->pcount)
	{
		i++;
		ptr->k = find_pipe(ptr, i);
		ptr->pid = fork();
		if (ptr->pid < 0)
			return ;
		if (ptr->pid == 0 && i == 0)
			ft_pid1(ptr, i);
		else if (ptr->pid == 0 && i < ptr->pcount)
			ft_pid2(ptr, i);
		else if (ptr->pid == 0 && i == ptr->pcount)
			ft_pid3(ptr, i);
	}
	ft_wait_close(ptr);
	free_fd(ptr, ptr->fd);
	free_array(ptr->pr);
	free_array(ptr->split_pr);
}
