/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:28:42 by llim              #+#    #+#             */
/*   Updated: 2021/03/15 21:30:17 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env)
{
	char	**env_list;
	int		len;
	int		i;

	len = check_env_length(env);
	env_list = (char **)malloc(sizeof(char *) * len);
	if (env_list == NULL)
		return ;
	i = 0;
	while (env)
	{
		env_list[i] = make_env_string(env->key, env->value);
		env = env->next;
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

void	update_env(t_env *head, char *key, char *value)
{
	t_env *env;

	env = find_env(head, key);
	if (env == NULL)
		add_env_back(&head, key, value);
	else if (env->value)
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
	else
	{
		env->value = ft_strdup(value);
	}
}

