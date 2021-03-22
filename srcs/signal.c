/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:51:53 by llim              #+#    #+#             */
/*   Updated: 2021/03/22 21:02:30 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\b\b  ", 4);
		write(1, "\nbash> ", 7);
	}
	else if (signo == SIGQUIT)
	{
		printf("\b\b");
	}
}
