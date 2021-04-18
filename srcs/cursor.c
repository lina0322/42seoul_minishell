/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:21:00 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 12:54:05 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_nbr_len(int n)
{
	int	ret;

	ret = 0;
	while (n > 0)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag)
{
	write(0, "\033[6n", 4);
	*read_ret = read(0, buf, 254);
	if (*read_ret < 0)
		*read_ret = 0;
	buf[*read_ret] = '\0';
	*i = 0;
	*flag = 0;
}

void	set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buf[255];
	int		read_ret;

	init_set_cursor(buf, &read_ret, &i, &flag);
	while (buf[++i])
	{
		if ('0' <= buf[i] && buf[i] <= '9')
		{
			if (flag == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				*col = ft_atoi(&buf[i]) - 1;
				break ;
			}
			flag++;
			i += get_nbr_len(*row) - 1;
		}
	}
}

void	set_cursor_win(t_state *s)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->max.col = w.ws_col;
	s->max.row = w.ws_row;
	set_cursor(&s->start.col, &s->start.row);
}
