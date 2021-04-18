/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:29:59 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 14:37:25 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_path(t_state *state)
{
	char	*path_env;
	char	**path_list;
	t_path	*path;
	int		i;

	(void)path;
	path_env = find_env_val(state->env_head, "PATH");
	path_list = ft_split(path_env, ':');
	path = state->path_head;
	i = 0;
	while (path_list[i])
	{
		add_path_back(&state->path_head, path_list[i]);
		i++;
	}
	free_2d(path_list);
}

void	add_path_back(t_path **head, char *path_str)
{
	t_path	*path;

	if (*head == NULL)
		*head = create_path(path_str);
	else
	{
		path = *head;
		while (path->next)
			path = path->next;
		path->next = create_path(path_str);
	}
}

t_path	*create_path(char *path_str)
{
	t_path	*path;

	if (!ft_calloc(1, sizeof(t_path), (void *)& path))
		exit(1);
	path->path = ft_strdup(path_str);
	path->next = 0;
	return (path);
}

void	free_path(t_path *path)
{
	t_path	*tmp;
	t_path	*next;

	tmp = path;
	while (tmp)
	{
		if (tmp->path)
			free(tmp->path);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

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
