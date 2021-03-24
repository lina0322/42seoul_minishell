/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:42:21 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/22 20:21:10 by dhyeon           ###   ########.fr       */
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
				{
					// (*i)--;
					return ;
				}
				j++;
			}
			(*i)++;
		}
		*flag = 1;
	}
}

void    ft_echo(t_state *t, t_cmd *cmd)
{
	int	i;
	int	flag;
	(void)cmd;
	(void)t;
	//test
	// char	*av[] = {"echo", "-nnnnnnnnn", "-n", "-n", "Hello", "World", 0};
	// int		ac = 6;
	// //test
	// char	*av[] = {"echo", "Hello", "World", 0};
	// int		ac = 3;
	// test
	char	*av[] = {"echo", "-nnnnnna", "Hello", "World", 0};
	int		ac = 4;

	flag = 0;
	i = 0;
	check_echo_flag(av, &i, &flag);
	while (i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i < ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}