/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:28:42 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 21:57:19 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env_head)
{
	char	**env_list;
	int		len;
	int		i;

	len = check_env_length(env_head);
	if (!ft_calloc(len, sizeof(char *), (void **)& env_list))
		return ;
	i = 0;
	while (env_head)
	{
		env_list[i] = make_env_string(env_head->key, env_head->value, env_head->has_equal);
		env_head = env_head->next;
		i++;
	}
	sorted_list(env_list, len);
	i = 0;
	while (i < len)
	{
		printf("declare -x %s\n", env_list[i]);
		i++;
	}
	free_2d(env_list);
}

void	print_one_export(t_env *head, char *key)
{
	t_env *env;

	env = find_env(head, key);
	if (env)
		printf("%s\n", env->value);
}

void	update_env(t_env *head, char *key, char *value, int has_equal)
{
	t_env *env;

	env = find_env(head, key);
	if (env == NULL)
		add_env_back(&head, key, value, has_equal);
	else
	{
		if (env->value)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = 0;
		}
		else
		{
			env->value = ft_strdup(value);
		}
		env->has_equal = has_equal;
	}
}
