/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:38:22 by llim              #+#    #+#             */
/*   Updated: 2021/03/15 21:30:01 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(char **envp, t_state *state)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				key = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				break;
			}
			j++;
		}
		add_env_back(&(state->env_head), key, value);
		i++;
	}
}

void	add_env_back(t_env **head, char *key, char *value)
{
	t_env *env;

	if (*head == NULL)
		*head = create_env(key, value);
	else
	{
		env = *head;
		while (env->next)
			env = env->next;
		env->next = create_env(key, value);
	}
}

t_env	*create_env(char *key, char *value)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (0);
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	return (env);
}

t_env	*find_env(t_env *head, char *key)
{
	t_env *env;

	env = head;
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_env_all(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s=\n", env->key);
		env = env->next;
	}
}

