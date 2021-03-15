/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:35:56 by llim              #+#    #+#             */
/*   Updated: 2021/03/15 20:50:41 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (i < len)
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
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(list[j], list[j+1], ft_strlen(list[j])) > 0)
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
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
