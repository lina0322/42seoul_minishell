/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 02:00:20 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 12:57:32 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_path(t_cmd *cmd, char *str)
{
	char	*tmp;
	char	*tmp2;

	(void)cmd;
	(void)tmp;
	tmp = cmd->av[0];
	tmp2 = ft_strjoin(str, "/");
	if (!tmp2)
		exit(1);
	cmd->av[0] = ft_strjoin(tmp2, cmd->av[0]);
	if (!cmd->av[0])
		exit(1);
	free(tmp);
	free(tmp2);
}

int		find_success_cmd(t_state *s, t_cmd *cmd, char *path, DIR *dir_ptr)
{
	make_path(cmd, path);
	closedir(dir_ptr);
	free_path(s->path_head);
	s->path_head = 0;
	return (1);
}

int		find_simple_cmd(t_cmd *cmd, int *err)
{
	struct stat	buf;

	if (stat(cmd->av[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			*err = 3;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		*err = 4;
		return (0);
	}
}

int		find_command(t_state *s, t_cmd *cmd)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	t_path			*p;

	parse_path(s);
	p = s->path_head;
	while (p)
	{
		dir_ptr = opendir(p->path);
		while (dir_ptr)
		{
			file = readdir(dir_ptr);
			if (file == 0)
				break ;
			else if (!ft_strcmp(file->d_name, ".")
					|| !ft_strcmp(file->d_name, ".."))
				continue ;
			else if (!ft_strcmp(cmd->av[0], file->d_name))
				return (find_success_cmd(s, cmd, p->path, dir_ptr));
		}
		p = p->next;
		closedir(dir_ptr);
	}
	free_path(s->path_head);
	return (0);
}

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
