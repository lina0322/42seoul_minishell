/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:28:42 by llim              #+#    #+#             */
/*   Updated: 2021/03/29 05:06:18 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env_head)
{
	char	**env_list;
	int		len;
	int		i;

	len = check_env_length(env_head);
	env_list = (char **)malloc(sizeof(char *) * len);
	if (env_list == NULL)
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
