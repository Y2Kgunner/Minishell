/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:20:08 by lel-khou          #+#    #+#             */
/*   Updated: 2022/11/02 23:48:44 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_redirections(t_data *ptr)
{
	int	j;

	ptr->flag = 0;
	ptr->rcount = 0;
	ptr->rcount1 = 0;
	ptr->hdcount = 0;
	ptr->flag = 0;
	j = ptr->k;
	while (ft_strcmp(ptr->pr[j], "|") != 0 && ptr->pr[j] != NULL)
	{
		if (ft_strcmp(ptr->pr[j], ">") == 0 || ft_strcmp(ptr->pr[j], ">>") == 0)
			ptr->rcount++;
		if (ft_strcmp(ptr->pr[j], "<") == 0)
		{
			ptr->rcount1++;
			if (j == ptr->k)
				ptr->flag = 1;
		}
		if (ft_strcmp(ptr->pr[j], "<<") == 0)
			ptr->hdcount++;
		j++;
	}
}

static void	out_redirections(t_data *ptr)
{
	int	file;
	int	j;

	j = ptr->k;
	while (ptr->rcount > 0)
	{
		if (ft_strcmp(ptr->pr[j], ">") == 0)
			file = open (ptr->split_pr[++ptr->k], O_WRONLY | O_CREAT | O_TRUNC, \
			0644);
		else if (ft_strcmp(ptr->pr[j], ">>") == 0)
			file = open(ptr->split_pr[++ptr->k], O_WRONLY | O_CREAT | O_APPEND, \
			0644);
		if (file == -1)
			return ;
		ptr->rcount--;
		j++;
		if (ptr->rcount == 0)
		{
			dup2(file, STDOUT_FILENO);
			close(file);
		}
	}
}

static void	in_redirections(t_data *ptr)
{
	int	file1;

	while (ptr->rcount1 > 0)
	{
		ptr->rcount1--;
		if (ptr->rcount1 == 0)
		{
			file1 = open (ptr->split_pr[++ptr->k], O_RDONLY);
			if (file1 == -1)
				return ;
			dup2(file1, STDIN_FILENO);
			close(file1);
		}
	}
}

static void	heredoc(t_data *ptr)
{
	char	*delimiter;
	char	*line;
	int		fd;

	delimiter = ft_strdup(ptr->split_pr[++ptr->k]);
	line = readline("> ");
	while (ft_strcmp(line, delimiter) != 0)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0700);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("> ");
	}
	close(fd);
	fd = open("temp", O_RDONLY, 0400);
	unlink("temp");
	dup2(fd, STDIN_FILENO);
	close (fd);
	free(delimiter);
	free(line);
}

void	ft_redirections(t_data *ptr, int i)
{
	count_redirections(ptr);
	if (ptr->hdcount > 0)
		heredoc(ptr);
	if (ptr->rcount == 0)
	{
		if (i != ptr->pcount)
		{
			dup2(ptr->fd[i][1], STDOUT_FILENO);
			close(ptr->fd[i][1]);
		}
		if (ptr->rcount1 == 0)
			return ;
	}
	if (ptr->flag == 1)
	{
		in_redirections(ptr);
		out_redirections(ptr);
	}
	else
	{
		out_redirections(ptr);
		in_redirections(ptr);
	}
}
