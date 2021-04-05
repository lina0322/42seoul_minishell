/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:58:57 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/06 04:47:32 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_backslash(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\\')
		return (1);
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
	s->col = w.ws_col;
	s->row = w.ws_row;
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

void	set_cursor(t_state *s)
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
				s->row = ft_atoi(&buf[i]) - 1;
			else
				s->col = ft_atoi(&buf[i]) - 1;
			flag++;
			i += get_nbr_len(s->col + 1) - 1;
		}
	}
}

char	*ft_strcjoin(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		if (ft_calloc(2, sizeof(char *), (void *)& ret))
			return (0); // exit 처리
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		if (ft_calloc(ft_strlen(str) + 2, sizeof(char *), (void *)& ret))
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
		print_save_char(s, (char)keycode);// input에 저장후 출력, 커서위치 변경
	}
}

void	term_loop(t_state *s)
{
	int	c;

	set_cursor_win(s);
	set_cursor(s);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		// printf("keycode : %d\n", c);//test
		if (c == '\n')
		{
			// if is_backslash
			// 커맨드 입력 처리
		}
		else
		{
			handle_keycode(s, c);
		}
		c = 0; // flush buffer
	}
}

void	prompt2(t_state *s)
{
	int	flag;
	(void)s;

	init_term(s);
	// write(1, "bash", 4);
	tputs("bash", 0, ft_putchar);
	flag = 0;
	while (1)
	{
		if (!flag)
			tputs("> ", 0, ft_putchar);
		term_loop(s);

	}
}
