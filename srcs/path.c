/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:29:59 by llim              #+#    #+#             */
/*   Updated: 2021/04/03 00:55:02 by llim             ###   ########.fr       */
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

	path = (t_path *)malloc(sizeof(t_path));
	if (path == NULL)
		return (0);
	path->path = ft_strdup(path_str);
	path->next = 0;
	return (path);
}
