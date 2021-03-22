/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:42:21 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/22 15:48:53 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_state *t, t_cmd *cmd)
{
	int	i;
	int	flag;
	(void)cmd;
	(void)t;
	//test
	char	*av[] = {"echo", "-n", "Hello", "World", 0};
	int		ac = 4;

	flag = 0;
	i = -1;
	if (!ft_strncmp(av[1], "-n\0", 3))
	{
		flag = 1;
		i++;
	}
	while (++i < ac - 1)
	{
		write(1, av[i + 1], ft_strlen(av[i + 1]));
		if (i < ac - 2)
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
}