/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:19:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/13 13:45:00 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_backslash_and_env(t_state *state, t_token *start)
{
	check_backslash(start);
	check_env(state, start);
}

void	check_backslash(t_token *token)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\\' &&
		(token->str[i + 1] == '\\' || token->str[i + 1] == '\"'))
		{
			tmp = ft_substr(token->str, 0, i);
			tmp2 = ft_strjoin2(tmp, &token->str[i + 1]);
			free(token->str);
			token->str = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
		}
		i++;
	}
}

void	check_env(t_state *state, t_token *token)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && token->str[i + 1])
		{
			if (i > 0 && token->str[i - 1] == '\\')
			{
				i++;
				continue ;
			}
			len = check_key_len(&token->str[i + 1]);
			key = ft_substr(&token->str[i + 1], 0, len);
			if (!ft_strcmp(key, "?"))
				i++;
			else
				change_str_to_env(state, token, key, i);
			free(key);
		}
		i++;
	}
}

int		check_key_len(char *str)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == ' ')
			break ;
		len++;
	}
	return (len);
}

void	change_str_to_env(t_state *state, t_token *token, char *key, int i)
{
	char	*value;
	char	*front;
	char	*front_value;
	char	*back;
	int		len;

	len = check_key_len(&token->str[i + 1]);
	value = ft_strdup(find_env_val(state->env_head, key));
	front = ft_substr(token->str, 0, i);
	front_value = ft_strjoin2(front, value);
	back = ft_substr(token->str, i + len + 1, ft_strlen(token->str) - len);
	free(token->str);
	token->str = ft_strjoin2(front_value, back);
	free(value);
	free(front);
	free(front_value);
	free(back);
}
