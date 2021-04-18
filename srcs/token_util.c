/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:41:40 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 19:39:43 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_operator(char *c, int i)
{
	if (c[i] == '\'')
		return (SINGLE);
	else if (c[i] == '\"')
		return (DOUBLE);
	else if (c[i] == '<')
		return (LEFT);
	else if (c[i] == '>')
	{
		if (c[i + 1] == '>')
			return (DOUBLERIGHT);
		return (RIGHT);
	}
	else if (c[i] == ';')
		return (SEMICOLON);
	else if (c[i] == '|')
		return (PIPE);
	else if (c[i] == ' ')
		return (SPACE);
	else if (c[i] == '\\')
		return (BACKSLASH);
	return (COMMON);
}

int		get_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i])
	{
		if (is_operator(input, i))
			break ;
		i++;
		len++;
	}
	return (len);
}

int		find_end(t_state *state, int type, int i)
{
	int		len;
	char	*input;

	len = 1;
	input = state->input;
	while (input[i])
	{
		if (type == SINGLE && input[i] == '\'')
			return (len);
		if (type == DOUBLE && input[i] == '\"')
		{
			if (input[i - 1] != '\\')
				return (len);
			else if (i >= 2)
			{
				if (!(check_backslash_count(input, i) % 2))
					return (len);
			}
		}
		len++;
		i++;
	}
	return (ERROR);
}

int		check_backslash_count(char *input, int i)
{
	int	count;

	count = 0;
	i--;
	while (i >= 0)
	{
		if (input[i] != '\\')
			break ;
		i--;
		count++;
	}
	return (count);
}

t_token	*create_token(char *str, int type)
{
	t_token *token;

	if (!ft_calloc(1, sizeof(t_token), (void *)&token))
		exit(1);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}
