/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:38:22 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 22:05:16 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

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
				break ;
			}
			j++;
		}
		add_env_back(&(state->env_head), key, value, TRUE);
		i++;
	}
	update_env(state->env_head, "OLDPWD", "", FALSE);
}

void	add_env_back(t_env **head, char *key, char *value, int has_equal)
{
	t_env *env;

	if (*head == NULL)
		*head = create_env(key, value, has_equal);
	else
	{
		env = *head;
		while (env->next)
			env = env->next;
		env->next = create_env(key, value, has_equal);
	}
}

t_env	*create_env(char *key, char *value, int has_equal)
{
	t_env *env;

	if (!ft_calloc(1, sizeof(t_env), (void *)& env))
		return (0);
	env->key = ft_strdup(key);
	env->has_equal = has_equal;
	env->next = 0;
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
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*find_env_val(t_env *head, char *key)
{
	t_env	*env;

	env = head;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_env_all(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->has_equal == TRUE)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			else
				printf("%s=\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}