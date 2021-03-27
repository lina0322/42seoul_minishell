/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:58:57 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/24 15:50:29 by llim             ###   ########.fr       */
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

void	handle_eof(char *input, int *flag)
{
	if (ft_strlen(input) == 0) // 입력값없이 컨트롤D 누른경우
	{
		printf("exit\n");
		free(input); // 모든 malloc 해제하는 함수 필요할듯
		exit(1);
	}
	else // 이전입력값이있고 eof로 컨트롤D한경우
	{
		printf(" \b\b");
		*flag = 1;
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
			handle_eof(state->input, &flag); //후에 bash나오게 수정
		else
		{
			state->input = input;
			break ;
		}
	}
}
