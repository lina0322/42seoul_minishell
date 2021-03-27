/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:41:40 by llim              #+#    #+#             */
/*   Updated: 2021/03/27 18:41:44 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_operator(char c)
{
	if (c == '\'')
		return (SINGLE);
	else if (c == '\"')
		return (DOUBLE);
	else if (c == '<')
		return (LEFT);
	else if (c == '>')
		return (RIGHT);
	else if (c == ';')
		return (SEMICOLON);
	else if (c == '|')
		return (PIPE);
	else if (c == ' ')
		return (SPACE);
	return (COMMON);
}

int		get_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i])
	{
		if (is_operator(input[i]))
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
