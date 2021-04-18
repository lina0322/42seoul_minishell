/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:24:33 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 13:03:47 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(t_state *s)
{
	tcgetattr(STDIN_FILENO, &s->t.term);
	s->t.term.c_lflag &= ~ICANON;
	s->t.term.c_lflag &= ~ECHO;
	s->t.term.c_cc[VMIN] = 1;
	s->t.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &s->t.term);
	tgetent(NULL, "xterm");
	s->t.cm = tgetstr("cm", NULL);
	s->t.ce = tgetstr("ce", NULL);
}

void	put_backspace(t_state *s)
{
	int	col;
	int	row;

	set_cursor(&col, &row);
	if (!s->input || (s->start.row >= row && s->start.col >= col))
		return ;
	col--;
	if (col < 0)
	{
		row -= 1;
		col = s->max.col;
	}
	tputs(tgoto(s->t.cm, col, row), 1, ft_putchar);
	tputs(s->t.ce, 1, ft_putchar);
	s->input = delete_last_char(s->input);
}

void	handle_keycode(t_state *s, int keycode)
{
	if (keycode == 4)
		handle_eof(s, s->input);
	else if (keycode == 127)
		put_backspace(s);
	else if (keycode == 4283163)
		press_up(s);
	else if (keycode == 4348699)
		press_down(s);
	else
	{
		if (ft_isprint((char)keycode))
			print_save_char(s, (char)keycode);
	}
}

int		term_loop(t_state *s)
{
	int	c;

	set_cursor_win(s);
	set_cursor(&s->cur.col, &s->cur.row);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			if (is_backslash(s))
				return (1);
			else
				return (0);
		}
		else
			handle_keycode(s, c);
		c = 0;
	}
	return (0);
}
