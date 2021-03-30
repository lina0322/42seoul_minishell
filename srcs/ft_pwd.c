/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:52:39 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/30 19:37:03 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_state *s, t_cmd *cmd)
{
	char	buf[999];

	(void)cmd;
	(void)s;
	if (!getcwd(buf, 999))
		return (-1); //에러처리
	else
		printf("%s\n", buf);
	return (0);
}

int	builtin(t_state *s, t_cmd *cmd)
{
	//test용
	(void)cmd;

	if (!ft_strcmp(s->input, "pwd")) // 나중에 input 대신 cmd의 명령어로 수정해야함
		ft_pwd(s, cmd);
	else if (!ft_strcmp(s->input, "echo"))
		ft_echo(s, cmd);
	else if (!ft_strcmp(s->input, "cd"))
		ft_cd(s, cmd);
	else if (!ft_strcmp(s->input, "env"))
		print_env_all(s->env_head);
	else if (!ft_strcmp(s->input, "export"))
		ft_export(s, cmd);
	else if (!ft_strcmp(s->input, "unset"))
		ft_unset(s, cmd);
	else if (!ft_strcmp(s->input, "exit"))
		ft_exit(s, cmd);
	else if (!ft_strcmp(s->input, "test"))
		find_command(s, cmd);
	return (0);
}
