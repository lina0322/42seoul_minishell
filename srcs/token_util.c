/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:41:40 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 12:27:10 by llim             ###   ########.fr       */
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

int		find_end(char *input, int type, int i)
{
	int	len;

	len = 1;
	while (input[i])
	{
		if ((type == SINGLE && input[i] == '\'')
		|| (type == DOUBLE && input[i] == '\"'))
			return (len);
		len++;
		i++;
	}
	return (ERROR);
}

void	free_token(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token;
		if (token->str)
			free(token->str);
		token = token->next;
		free(tmp);
	}
}
