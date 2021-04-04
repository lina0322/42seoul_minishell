/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:29:59 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 21:58:44 by llim             ###   ########.fr       */
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
}

void	add_path_back(t_path **head, char *path_str)
{
	t_path *path;

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
	t_path *path;

	if (!ft_calloc(1, sizeof(t_path), (void *)& path))
		return (0);
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
		if (path->path)
			free(path->path);
		next = path->next;
		free(tmp);
		tmp = next;
	}
}
