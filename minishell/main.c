/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:30:16 by lel-khou          #+#    #+#             */
/*   Updated: 2022/11/02 23:47:59 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	check_commands(t_data *ptr)
{
	int	i;

	i = 0;
	while (ptr->s[i] != 0)
	{
		if ((ptr->s[i] == '|' || ptr->s[i] == '<' || ptr->s[i] == '>') \
		&& ptr->dq == 0 && ptr->sq == 0)
		{
			ptr->prcount++;
			if (ptr->s[i + 1] == '<' || ptr->s[i + 1] == '>')
				i++;
		}
		if (ptr->s[i] == 39 || ptr->s[i] == 34)
		{
			if (ptr->s[i] == 39 && ptr->dq == 0 && ptr->sq == 0)
				ptr->dq = 1;
			else if (ptr->s[i] == 39 && ptr->dq != 0 && ptr->sq == 0)
				ptr->dq = 0;
			if (ptr->s[i] == 34 && ptr->sq == 0 && ptr->dq == 0)
				ptr->sq = 1;
			else if (ptr->s[i] == 34 && ptr->sq != 0 && ptr->dq == 0)
				ptr->sq = 0;
		}
		i++;
	}
}

void	sighandler(int signum)
{
	if (sig_count(0) && signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 1;
	}
}

void	single_command(t_data *ptr)
{
	ptr->s = var_expander(ptr, ptr->s);
	ptr->arv = ft_split_single(ptr);
	ft_remove_space(ptr);
	ft_set_(ptr);
	single_parse(ptr);
	ft_free_single(ptr);
}

static void	rl_loop(t_data *ptr)
{
	while (1)
	{
		g_sig = 0;
		while (g_sig != 1)
		{
			ptr->s = readline("Minishell >> ");
			if (ptr->s == NULL)
			{
				ft_free_init(ptr);
				exit (0);
			}
			if (ft_strlen(ptr->s) > 0)
				add_history(ptr->s);
			check_commands(ptr);
			if (ptr->prcount == 0)
				single_command(ptr);
			else
				ft_pipe(ptr);
			ptr->prcount = 0;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*ptr;

	(void)argc;
	(void)argv;
	ptr = (t_data *)malloc(sizeof(t_data));
	if (!ptr)
		return (0);
	ft_initialize(ptr, envp);
	rl_catch_signals = 0;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	rl_loop(ptr);
	return (0);
}
