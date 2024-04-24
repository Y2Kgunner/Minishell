/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:47:31 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/11/02 23:48:57 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_count(int status)
{
	static int	child;

	if (status == 1)
		child = 1;
	if (status == 2)
		child = 0;
	if (child == 1)
		return (0);
	return (1);
}
