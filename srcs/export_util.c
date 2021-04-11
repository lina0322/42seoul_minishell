/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:35:56 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 21:49:48 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_env_length(t_env *head)
{
	int		len;
	t_env	*env;

	env = head;
	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	*make_env_string(char *key, char *value, int has_equal)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = check_len(key, value, has_equal);	
	if (!ft_calloc(len, sizeof(char), (void *)& result))
		return (0);
	i = 0;
	j = 0;
	while (key[i])
		result[j++] = key[i++];
	if (has_equal == TRUE)
	{
		result[j++] = '=';
		i = 0;
		if (value)
		{
			result[j++] = '\"';
			while (value[i])
				result[j++] = value[i++];
			result[j++] = '\"';
		}
	}
	result[j] = '\0';
	return (result);
}

int		check_len(char *key, char *value, int has_equal)
{
	int len;

	len = 0;
	if (has_equal == FALSE)
	{
		len = ft_strlen(key) + 1;
	}
	else if (has_equal == TRUE)
	{
		if (value)
			len = ft_strlen(key) + ft_strlen(value) + 4;
		else
			len = ft_strlen(key) + 2;
	}
	return len;
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
			if (ft_strncmp(list[j], list[j + 1], ft_strlen(list[j])) > 0)
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
