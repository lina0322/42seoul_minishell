/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:42:21 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/17 06:32:06 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_echo_flag(char **av, int *i, int *flag)
{
	int	j;

	*i = 1;
	if (av[1] && av[*i][0] == '-' && av[*i][1] == 'n')
	{
		while (av[*i][0] == '-' && av[*i][1] == 'n')
		{
			j = 1;
			while (av[1][j] != '\0')
			{
				if (av[1][j] != 'n')
					return ;
				j++;
			}
			(*i)++;
		}
		*flag = 1;
	}
}

void	ft_echo(t_state *s, t_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	check_echo_flag(cmd->av, &i, &flag);
	while (i < cmd->ac)
	{
		write(1, cmd->av[i], ft_strlen(cmd->av[i]));
		if (i < cmd->ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	s->ret = 0;
}
