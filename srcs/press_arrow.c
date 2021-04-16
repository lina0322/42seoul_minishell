/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 03:32:15 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/17 03:35:50 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	move_cursor(t_state *s)
{
	t_keypos	pos;
	int	len;

	if (s->input != 0)
		len = ft_strlen(s->input);
	else
		len = 0;
	set_cursor(&pos.col, &pos.row);
	pos.col -= len;
	if (pos.col < 0)
	{
		pos.row--;
		pos.col = s->max.col + pos.col;
	}
	tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

void	press_up(t_state *s)
{
	// t_keypos	pos;
	// int			len;

	if (!s->save_head)
		return ;
	if (s->input != 0 && s->s_flag == 0)
		s->save_head = push_front_save(s->input, s->save_head, 0);
	if (s->save_head->next != 0 && s->s_flag != 0)
		s->save_head = s->save_head->next;
	s->s_flag = 1;
	move_cursor(s);
	// test_save(s);
	// if (s->input != 0)
	// 	len = ft_strlen(s->input);
	// else
	// 	len = 0;
	// set_cursor(&pos.col, &pos.row);
	// pos.col -= len;
	// if (pos.col < 0)
	// {
	// 	pos.row--;
	// 	pos.col = s->max.col + pos.col;
	// }
	// tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
	// tputs(tgetstr("ce", NULL), 1, ft_putchar);
	write(1, s->save_head->input, ft_strlen(s->save_head->input));
	if (s->input)
		free(s->input);
	s->input = ft_strdup(s->save_head->input);
}

void	press_down(t_state *s)
{
	// t_keypos	pos;
	// int			len;

	if (s->save_head == 0)
		return ;
	move_cursor(s);
	// if (s->input != 0)
	// 	len = ft_strlen(s->input);
	// else
	// 	len = 0;
	// set_cursor(&pos.col, &pos.row);
	// pos.col -= len;
	// if (pos.col < 0)
	// {
	// 	pos.row--;
	// 	pos.col = s->max.col + pos.col;
	// }
	// tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
	// tputs(tgetstr("ce", NULL), 1, ft_putchar);
	if (s->input)
		free(s->input);
	s->input = 0;
	if (s->save_head->prev == 0)
		return ;
	write(1, s->save_head->prev->input, ft_strlen(s->save_head->prev->input));
	s->input = ft_strdup(s->save_head->prev->input);
	// if (s->save_head->prev->pre != 0)
		s->save_head = s->save_head->prev;
}
