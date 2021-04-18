/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:33:38 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 19:35:52 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_state *s, t_cmd *cmd)
{
	set_pipe(cmd);
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(s, cmd);
	else if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(s, cmd);
	else if (!ft_strcmp(cmd->av[0], "cd"))
		ft_cd(s, cmd);
	else if (!ft_strcmp(cmd->av[0], "env"))
		print_env_all(s->env_head);
	else if (!ft_strcmp(cmd->av[0], "export"))
		ft_export(s, cmd, 0);
	else if (!ft_strcmp(cmd->av[0], "unset"))
		ft_unset(s, cmd);
	else if (!ft_strcmp(cmd->av[0], "exit"))
		ft_exit(s, cmd);
}

void	set_fork_builtin(t_state *s, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		execute_builtin(s, cmd);
		exit(s->ret);
	}
	else
	{
		close(cmd->pip[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			s->ret = WEXITSTATUS(status);
	}
}

int		builtin(t_state *s, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->av[0], "pwd") || !ft_strcmp(cmd->av[0], "echo")
		|| !ft_strcmp(cmd->av[0], "env"))
	{
		set_fork_builtin(s, cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd->av[0], "cd") || !ft_strcmp(cmd->av[0], "exit")
		|| !ft_strcmp(cmd->av[0], "export") || !ft_strcmp(cmd->av[0], "unset"))
	{
		execute_builtin(s, cmd);
		return (1);
	}
	else
		return (0);
}
