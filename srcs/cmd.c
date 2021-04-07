/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 02:00:20 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/08 05:25:50 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *av[] = {"grep", "-al", 0}; //

void	make_path(t_cmd *cmd, char *str)
{
	char	*tmp;
	char	*tmp2;

	(void)cmd;
	(void)tmp;
	tmp = av[0];
	tmp2 = ft_strjoin(str, "/");
	if (!tmp2)
		return ; //exit
	av[0] = ft_strjoin(tmp2, av[0]);
	if (!av[0])
		return ; //exit
	printf("%s\n", av[0]);
	// free(tmp);
	free(tmp2);
}

int	find_success_cmd(t_state *s, t_cmd *cmd, char *path, DIR *dir_ptr)
{
	make_path(cmd, path);
	closedir(dir_ptr);
	free_path(s->path_head);
	return (1);
}

int	find_command(t_state *s, t_cmd *cmd) // 찾으면 1 못찾으면 0
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
			else if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
				continue ;
			else if (!ft_strcmp(av[0], file->d_name))
				return (find_success_cmd(s, cmd, p->path, dir_ptr));
		}
		p = p->next;
	}
	closedir(dir_ptr);
	free_path(s->path_head);
	return (0);
}

int		builtin(t_state *s, t_cmd *cmd)
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
	else
		return (0);
	return (1);
}
