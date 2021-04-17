/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:19:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 00:46:58 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_backslash_and_env(t_state *state, t_token *start)
{
	check_backslash(start);
	check_env(state, start);
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

void	check_env(t_state *state, t_token *token)
{
	int		i;
	int		len;
	char	*key;
	char	*value;
	char	*temp;

	i = 0;
	while (token->str[i])
	{
		value = NULL;
		len = 0;
		if (token->str[i] == '$')
		{
			if (i > 0 && token->str[i - 1] == '\\')
				i--;
			else if (token->str[i + 1])
			{
				len = check_key_len(&token->str[i + 1]);
				key = ft_substr(&token->str[i + 1], 0, len);
				if (!ft_strcmp(key, "?"))
					value = ft_itoa(state->ret);
				else
					value = ft_strdup(find_env_val(state->env_head, key));
				free(key);
			}
			temp = changed_str(token->str, i, i + len, value);
			free(token->str);
			if (temp)
			{
				token->str = ft_strdup(temp);
				free(temp);
			}
			free(value);
		}
		if (!token->str || !token->str[i])
			break;
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

char    *changed_str(char *origin, int start, int end, char *insert)
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

void	check_env_space(t_state *state)
{
	t_token *token;
	char	*temp;

	token = state->token_head;
	while (token)
	{
		if (!ft_strcmp(token->str, "echo"))
		{
			token = token->next;
			while (token && token->type != SEMICOLON && token->type != PIPE)
			{
				if (token->type == COMMON)
				{
					temp = removed_space(token->str);
					free(token->str);
					if (temp)
					{
						token->str = ft_strdup(temp);
						free(temp);
					}
					else
						token->str = 0;
				}
				token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}

char	*removed_space(char *str)
{
	char	**strs;
	char	*result;
	char	*temp;
	char	*temp2;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	result = 0;
	temp = 0;
	while (strs[i])
	{
		if (i != 0)
			temp = ft_strjoin2(result, " ");
		temp2 = ft_strjoin2(temp, strs[i]);
		free(result);
		result = ft_strdup(temp2);
		free(temp);
		free(temp2);
		i++;
	}
	return result;
}
