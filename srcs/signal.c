/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:51:53 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 19:36:56 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		if (g_state.is_fork == 0)
		{
			write(1, "\nbash> ", 7);
			if (g_state.input)
				free(g_state.input);
			g_state.input = 0;
		}
		else
		{
			g_state.ret = 130;
			write(1, "\n", 1);
		}
	}
	else if (signo == SIGQUIT)
	{
		if (g_state.is_fork == 1)
		{
			g_state.ret = 131;
			write(1, "Quit: 3\n", 9);
		}
	}
}
