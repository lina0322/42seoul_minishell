/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:21:00 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/14 21:58:13 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbr_len(int n)
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

void	set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buf[255];
	int		read_ret;

	write(0, "\033[6n", 4);
	read_ret = read(0, buf, 254);
	buf[read_ret] = '\0';
	// printf("\nreadret : %d\nbuf : %s\n",read_ret, buf);
	// for (int i = 0 ; i < read_ret ; i++)
	// 	printf("%d %c\n", buf[i], buf[i]);
	i = 0;
	flag = 0;
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
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->max.col = w.ws_col;
	s->max.row = w.ws_row;
	set_cursor(&s->start.col, &s->start.row);
}
