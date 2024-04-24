/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lel-khou <lel-khou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:52:48 by lel-khou          #+#    #+#             */
/*   Updated: 2022/11/02 17:44:02 by lel-khou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pipe(t_data *ptr, int i)
{
	int	pipe;
	int	l;

	pipe = 0;
	l = 0;
	if (i == 0)
		return (0);
	while (ptr->pr[l] != 0 && pipe < i)
	{
		if (ft_strcmp(ptr->pr[l], "|") == 0)
			pipe++;
		l++;
	}
	return (l);
}

void	ft_wait_close(t_data *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->pcount)
	{
		close(ptr->fd[i][0]);
		close(ptr->fd[i][1]);
		i++;
	}
	i = 0;
	while (i <= ptr->pcount)
	{
		wait (NULL);
		i++;
	}
}
