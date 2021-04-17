/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:19:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/17 23:24:02 by dhyeon           ###   ########seoul.kr  */
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
	char	*value;

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
				value = ft_itoa(state->ret);
			else
				value = ft_strdup(find_env_val(state->env_head, key));
			token->str = change_str(token->str, i, i + len, value);
			free(value);
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

char    *change_str(char *origin, int start, int end, char *insert)
{
    char    *result;
    char    *front;
    char    *front_insert;
    char    *back;

    front = ft_substr(origin, 0, start);
    front_insert = ft_strjoin2(front, insert);
    back = ft_substr(origin, end + 1, ft_strlen(origin) - (end - start));
    result = ft_strjoin2(front_insert, back);
    free(front);
    free(back);
	free(front_insert);
    return (result);
}
