/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:19:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 20:26:15 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_backslash_and_env(t_state *state, t_token *start)
{
	check_backslash(start);
	check_dollar_sign(state, start);
	check_env_space(state);
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

void	check_dollar_sign(t_state *state, t_token *token)
{
	int		i;
	char	*value;
	char	*temp;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			value = NULL;
			temp = check_env(state, token, value, &i);
			free(value);
			free(token->str);
			if (temp)
			{
				token->str = ft_strdup(temp);
				free(temp);
			}
		}
		if (!token->str || !token->str[i])
			break ;
		i++;
	}
}

char	*check_env(t_state *state, t_token *token, char *value, int *i)
{
	int		len;
	char	*key;
	char	*temp;

	len = 0;
	if (*i > 0 && token->str[*i - 1] == '\\')
		*i = *i - 1;
	else if (token->str[*i + 1])
	{
		len = check_key_len(&token->str[*i + 1]);
		key = ft_substr(&token->str[*i + 1], 0, len);
		if (!ft_strcmp(key, "?"))
		{
			temp = ft_itoa(state->ret);
			value = ft_strdup(temp);
			free(temp);
		}
		else
			value = ft_strdup(find_env_val(state->env_head, key));
		free(key);
	}
	return (changed_str(token->str, *i, *i + len, value));
}

char	*changed_str(char *origin, int start, int end, char *insert)
{
	char	*result;
	char	*front;
	char	*front_insert;
	char	*back;

	front = ft_substr(origin, 0, start);
	front_insert = ft_strjoin2(front, insert);
	back = ft_substr(origin, end + 1, ft_strlen(origin) - (end - start));
	result = ft_strjoin2(front_insert, back);
	free(front);
	free(back);
	free(insert);
	free(front_insert);
	return (result);
}
