/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:32 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/08 06:20:00 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_state *s, t_cmd *cmd)
{
	if (!builtin(s, s->cmd_head)) // builtin 아닐때
	{
		if (!find_command(s, cmd)) // 패스 함수도 아닐때!
			printf("bash: %s: command not found\n", s->input); //cmd->av[0]로 수정, 문자일때만 처리, 아닐땐 무시
		else //패스함수일때!
		{

		}
	}
	//history 저장 input 그대로 저장하면 됨
}
