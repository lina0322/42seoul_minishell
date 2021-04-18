/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 13:50:40 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_syntax_error(int cur_type, int next_type, int has_space)
{
	int	type;

	type = next_type;
	if (cur_type == ERROR_NULL && next_type >= PIPE)
	{
		if (next_type == PIPE)
			type = ERROR_PIPE;
		else if (next_type == SEMICOLON)
			type = ERROR_COLON;
	}
	else if ((cur_type >= PIPE || cur_type <= ERROR_PIPE) && next_type >= PIPE)
	{
		type = check_deep_syntax_error(cur_type, next_type, has_space);
	}
	return (type);
}

int		check_deep_syntax_error(int cur_type, int next_type, int has_space)
{
	int	type;

	type = next_type;
	if (cur_type == PIPE || cur_type == ERROR_PIPE)
	{
		if (next_type == PIPE)
			type = ERROR_PIPE2;
		else if (next_type == SEMICOLON)
			type = ERROR_COLON;
		else if (has_space)
			type = ERROR_PIPE;
	}
	else if (cur_type == SEMICOLON || cur_type == ERROR_COLON)
	{
		if (next_type == SEMICOLON)
			type = ERROR_COLON2;
		else if (next_type == PIPE)
			type = ERROR_PIPE;
		else if (has_space)
			type = ERROR_COLON;
	}
	return (type);
}

void	check_token_error(t_state *state)
{
	t_token	*token;

	token = state->token_head;
	while (token)
	{
		if (token->type <= ERROR_QUOTE)
			return (return_quote_error(state, token));
		else if (token->type >= 4 && token->type <= 6)
		{
			if (!token->next || token->next->type == SEMICOLON ||
			token->next->type == PIPE)
			{
				make_cmd(state, token, 1, ERROR_RDIR);
				free_token(state->token_head);
				return ;
			}
		}
		token = token->next;
	}
	parse_cmd(state, 0);
	free_token(state->token_head);
}

void	return_quote_error(t_state *state, t_token *token)
{
	int		type;

	type = token->type;
	if (token->next)
	{
		if (token->next->type <= ERROR_PIPE2)
			type = token->next->type;
	}
	make_cmd(state, token, 1, type);
	free_token(state->token_head);
}
