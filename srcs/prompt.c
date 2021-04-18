/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:58:57 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 13:02:21 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_backslash(t_state *s)
{
	int		flag;
	int		i;
	char	*str;

	if (s->input == 0 || ft_strlen(s->input) == 0)
		return (0);
	str = s->input;
	flag = -1;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == '\\' && i >= 0)
	{
		flag *= -1;
		i--;
	}
	if (flag == 1)
	{
		s->input = delete_last_char(str);
		return (1);
	}
	else
		return (0);
}

void	handle_eof(t_state *s, char *input)
{
	if (!input)
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &s->t.save);
		exit(1);
	}
}

void	prompt2(t_state *s)
{
	write(1, "bash", 4);
	init_term(s);
	while (1)
	{
		write(1, "> ", 2);
		if (term_loop(s) == 0)
		{
			reset_save(s);
			break ;
		}
		else
			continue ;
	}
}
