/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:32 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/08 05:30:27 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_state *s, t_cmd *cmd)
{
	if (!builtin(state, state->cmd_head)) // builtin 아닐때
	{
		if (!find_command(s, cmd)) // 패스 함수도 아닐때!
			printf("bash: %s: command not found\n", cmd->av[0]);
	}
}
