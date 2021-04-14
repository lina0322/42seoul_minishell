/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:24:33 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/14 22:21:06 by dhyeon           ###   ########.fr       */
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
	// printf("col : %d\nstart : %d\n", col, s->start.col);
	// printf("col : %d\nrow : %d\ninput : %s\n", s->start.col, s->start.row, s->input);
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

void	test_save(t_state *s)
{
	t_save *tmp;

	tmp = s->save_head;

	while (tmp->prev != 0)
		tmp = tmp->prev;
	printf("\n========================\n");
	while (tmp)
	{
		printf("list : %s\n", tmp->input);
		tmp = tmp->next;
	}
	printf("========================\n");
}

// int	check_save_flag(t_save *save)
// {
// 	t_save	*tmp;

// 	tmp = save;
// 	while (tmp->prev)
// 		tmp = tmp->prev;
// 	while (tmp)
// 	{
// 		if (tmp->)
// 	}
// }

void	press_up(t_state *s)
{
	(void)s;
	t_save		*tmp;
	t_keypos	pos;
	int			len;

	if (!s->save_head)
		return ;
	if (s->input != 0 && s->s_flag == 0)
	{
		// printf("in in \n");
		// printf("s->input : %s\n s->save_head : %p\n s->sh->input: %s\n", s->input, s->save_head, s->save_head->input);
		tmp = create_save(s->input, s->save_head, 0);
		s->save_head = tmp;
	}
	s->s_flag = 1;
	test_save(s);
	if (s->input != 0)
		len = ft_strlen(s->input);
	else
		len = 0;
	set_cursor(&pos.col, &pos.row);
	while (len)
	{
		tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		len--;
	}
	// pos.col = s->start.col + ft_strlen(s->save_head->input);
	// pos.row = s->cur.row;
	// if (pos.col > s->max.col)
	// {
	// 	pos.col -= s->max.col;
	// 	pos.row += 1;
	// }
	// tputs(tgoto(s->t.cm, s->start.col, s->start.row), 1, ft_putchar);
	write(1, s->save_head->input, ft_strlen(s->save_head->input));
	// tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
	free(s->input);
	s->input = ft_strdup(s->save_head->input);
	s->save_head = s->save_head->next;
}

void	press_down(t_state *s)
{
	(void)s;
}

void	handle_keycode(t_state *s, int keycode)
{
	// set_cursor_win(s);
	// set_cursor(s);
	if (keycode == 4) // ctrl + D
	{
		handle_eof(s->input);
	}
	else if (keycode == 127) // backspace
	{
		put_backspace(s);
		// write(1, "backspace\n", 11);
		// 출력된 문자, 저장된 문자 지우고 커서 옮기기
	}
	else if (keycode == 4283163) // up
	{
		// write(1, "up\n", 3);
		press_up(s);
	}
	else if (keycode == 4348699) // down
	{
		write(1, "down\n", 5);
		press_down(s);
	}
	else // 문자 붙이기
	{
		if (ft_isprint((char)keycode))
			print_save_char(s, (char)keycode);// input에 저장후 출력, 커서위치 변경
	}
	// printf("input : %s\n", s->input);
}

int	term_loop(t_state *s)
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
