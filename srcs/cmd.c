/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 02:00:20 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 21:38:22 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	struct dirent	*f;
	t_path			*p;

	parse_path(s);
	p = s->path_head;
	while (p)
	{
		dir_ptr = opendir(p->path);
		while (dir_ptr)
		{
			f = readdir(dir_ptr);
			if (f == 0)
				break ;
			else if (!ft_strcmp(f->d_name, ".") || !ft_strcmp(f->d_name, ".."))
				continue ;
			else if (!ft_strcmp(cmd->av[0], f->d_name))
				return (find_success_cmd(s, cmd, p->path, dir_ptr));
		}
		p = p->next;
		closedir(dir_ptr);
	}
	free_path(s->path_head);
	s->path_head = 0;
	return (0);
}
