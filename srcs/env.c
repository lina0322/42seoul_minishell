/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:38:22 by llim              #+#    #+#             */
/*   Updated: 2021/04/20 12:26:41 by llim             ###   ########.fr       */
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
				break ;
			}
			j++;
		}
		add_env_back(&(state->env_head), key, value, TRUE);
		free(key);
		free(value);
		i++;
	}
	update_env(state->env_head, "OLDPWD", "", FALSE);
}

void	add_env_back(t_env **head, char *key, char *value, int has_equal)
{
	t_env	*env;

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
	t_env	*env;

	if (!ft_calloc(1, sizeof(t_env), (void *)&env))
		exit(1);
	env->key = ft_strdup(key);
	env->has_equal = has_equal;
	env->next = 0;
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("");
	return (env);
}

void	change_dollar_sign(int i)
{
	int		len;
	char	*key;
	char	*temp;
	char	*value;
	char	*input;

	input = g_state.input2;
	len = check_key_len(&input[i + 1], TRUE);
	key = ft_substr(&input[i + 1], 0, len);
	if (!ft_strcmp(key, "?"))
	{
		temp = ft_itoa(g_state.ret);
		value = ft_strdup(temp);
		free(temp);
	}
	else
		value = ft_strdup(find_env_val(g_state.env_head, key));
	free(key);
	temp = changed_str(input, i, i + len, value);
	free(g_state.input2);
	g_state.input2 = ft_strdup(temp);
	free(temp);
}
