/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:52:39 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/16 02:22:01 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_state *state, t_cmd *cmd)
{
	char	buf[999];

	(void)cmd;
	(void)state;
	if (!getcwd(buf, 999))
		return (-1); //에러처리
	else
		printf("%s\n", buf);
	return (0);
}

int	builtin(t_state *state, t_cmd *cmd)
{
	//test용
	(void)cmd;

	if (!ft_strncmp(state->input, "pwd", 3)) // 나중에 input 대신 cmd의 명령어로 수정해야함
		ft_pwd(state, cmd);
	// else if (!ft_strncmp(state->input, "echo", 4))
		// ft_echo(state, cmd);
	else if (!ft_strncmp(state->input, "cd", 2))
		ft_cd(state, cmd);
	else if (!ft_strncmp(state->input, "env", 3))
		print_env_all(state->env_head);
	// else if (!ft_strncmp(state->input, "export", 6))
	// 	ft_export(state, cmd);
	// else if (!ft_strncmp(state->input, "unset", 5))
	// 	ft_unset(state, cmd);
	else if (!ft_strncmp(state->input, "exit", 4))
		ft_exit(state, cmd);
	return (0);
}
