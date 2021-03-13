/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:38:22 by llim              #+#    #+#             */
/*   Updated: 2021/03/13 16:29:47 by llim             ###   ########.fr       */
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

void	print_env_all(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_export_sorted_list(t_env *env)
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
		env_list[i] = make_export_env(env->key, env->value);
		env = env->next;
		i++;
	}
	sorted_list(env_list, len);
	i = 0;
	while (env_list[i])
	{
		printf("declare -x %s\n", env_list[i]);
		i++;
	}
}

int		check_env_length(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char 	*make_export_env(char *key, char *value)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(key) + ft_strlen(value) + 4;
	result = (char *)malloc(sizeof(char) * len);
	if (result == NULL)
		return (0);
	i = 0;
	j = 0;
	while (key[i])
		result[j++] = key[i++];
	result[j++] = '=';
	result[j++] = '\"';
	i = 0;
	while (value[i])
		result[j++] = value[i++];
	result[j++] = '\"';
	result[j] = '\0';
	return (result);
}

void	sorted_list(char **list, int size)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(list[j], list[j+1], ft_strlen(list[j])) > 0)
			{
			//	printf("%s, %s\n", list[j], list[j+1]);
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
