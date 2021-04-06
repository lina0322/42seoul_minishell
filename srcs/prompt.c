/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:58:57 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/06 22:37:55 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_backslash(char *str)
{
	int	flag;
	int	i;

	if (str == 0)
		return (0);
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
	if (flag == 1) // 마지막 백슬래시 지워주는 함수 추가
	{
		delete_last_char(str);
		return (1);
	}
	else
		return (0);
}

void	handle_eof(char *input)
{
	if (input) // 입력값없이 컨트롤D 누른경우
	{
		printf("exit\n");
		free(input); // 모든 malloc 해제하는 함수 필요할듯
		exit(1);
	}
}

void	prompt(t_state *state)
{
	int		gnl; //gnl return
	int		flag; //추가 입력인지 체크하는 flag
	char	*input;

	flag = 0;
	write(1, "bash", 4);
	while (1)
	{
		if (!flag)
			write(1, "> ", 2);
		gnl = get_next_line(0, &input);
		state->input = ft_strjoin2(state->input, input);
		if (is_backslash(state->input))
		{
			state->input[ft_strlen(state->input) - 1] = '\0';
			flag = 0;
		}
		else if (gnl == 0) // 컨트롤 + D 입력경우 eof
			handle_eof(state->input); //후에 bash나오게 수정
		else
		{
			state->input = input;
			break ;
		}
	}
}

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

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	set_cursor_win(t_state *s)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->max_col = w.ws_col;
	s->max_row = w.ws_row;
}

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

char	*ft_strcjoin(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		if (!ft_calloc(2, sizeof(char *), (void *)& ret))
			return (0); // exit 처리
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		if (!ft_calloc(ft_strlen(str) + 2, sizeof(char *), (void *)& ret))
			return (0); // exit 처리
		i = -1;
		while (str[++i])
			ret[i] = str[i];
		ret[i] = c;
		ret[i + 1] = '\0';
		free(str);
	}
	return (ret);
}

void	print_save_char(t_state *s, char c)
{
	s->input = ft_strcjoin(s->input, c);
	write(1, &c, 1);
}

void	delete_last_char(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!ft_calloc(len, sizeof(char *), (void *)& tmp))
		return ; //exit 처리
	i = 0;
	while (str[i + 1])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len] = '\0';
	free(str);
	str = tmp;
}

void	put_backspace(t_state *s)
{
	int	col;
	int	row;

	if (!s->input)
		return ;
	set_cursor(&col, &row);
	col--;
	if (col < 0)
	{
		row -= 1;
		col = s->max_col;
	}
	tputs(tgoto(s->t.cm, col, row), 1, ft_putchar);
	tputs(s->t.ce, 1, ft_putchar);
	// delete_last_char(s->input);
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
		write(1, "up\n", 3);
	}
	else if (keycode == 4348699) // down
	{
		write(1, "down\n", 5);
	}
	else // 문자 붙이기
	{
		//if printable 해서 출력가능문자만 받자
		print_save_char(s, (char)keycode);// input에 저장후 출력, 커서위치 변경
	}
}

int	term_loop(t_state *s)
{
	int	c;

	set_cursor_win(s);
	set_cursor(&s->col, &s->row);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		// printf("[[[col : %drow : %d]]]", s->col, s->row);
		// printf("keycode : %d\n", c);//test
		if (c == '\n')
		{
			if (is_backslash(s->input))
			{
				write(1, "\n", 1);
				return (1);
			}
			else
				return (0);
			// if is_backslash
			// 커맨드 입력 처리
			// break ;
		}
		else
		{
			handle_keycode(s, c);
		}
		c = 0; // flush buffer
	}
	return (0);
}

void	prompt2(t_state *s)
{
	// int	flag;
	(void)s;

	init_term(s);
	write(1, "bash", 4);
	// tputs("bash", 0, ft_putchar);
	// flag = 0;
	while (1)
	{
		// if (!flag)
			write(1, "> ", 2); // 이부분 나중에 수정, 반복문도 빼고 \ 입력 받앗을때만 > 출력하고 입력받도록 해보자
		// else
		// 	break ;
		if (term_loop(s) == 0)
			break ;
		else
			continue ;
	}
}
