/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:38:22 by llim              #+#    #+#             */
/*   Updated: 2021/03/12 23:41:00 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_env(char **envp, t_state *state)
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
		add_back_env(&(state->env_head);
		i++;
	}
}

void add_env_back(t_env **head, char *key, char *value)
{
	t_env *temp;

	if (*head == NULL)
		*head = create_env(key, value);
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = create_env(key, value);
	}
}

t_env *create_env(char *key, char *value)
{
	t_env *env;

	if (!(env = (t_env *)ft_calloc(1, sizeof(t_env))))
		return (0);
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value;
	return (env)
}
