/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/04/15 01:13:55 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_state *state)
{
	int		type;
	int		count;
	int		i;

	if (!state->input)
		return ;
	i = 0;
	while (state->input[i])
	{
		count = 1;
		if (!(type = is_operator(state->input, i)))
			count = get_len(state->input, i);
		else if (type == DOUBLERIGHT || type == BACKSLASH)
			count = 2;
		else if (type == SINGLE || type == DOUBLE)
			if (!(count = find_end(state->input, type, ++i)))
			{
				i = make_token(state, 1, i - 1, ERROR_QUOTE);
				break ;
			}
		i = make_token(state, count, i, type);
	}
	// print_token(state);
	check_token_error(state);
}

void	check_token_error(t_state *state)
{
	t_token	*token;
	int		type;

	token = state->token_head;
	while (token)
	{
		if (token->type <= ERROR_QUOTE)
		{
			type = token->type;
			if (token->next)
			{
				if (token->next->type <= ERROR_PIPE2)
					type = token->next->type;
			}
			make_cmd(state, token, 1, type);
			free_token(state->token_head);
			// print_cmd2(state);
			return;
		}
		token = token->next;
	}
	parse_cmd(state);
	free_token(state->token_head);
}

int		make_token(t_state *state, int count, int i, int type)
{
	char	*token_str;
	int		j;

	if (!ft_calloc(count + 1, sizeof(char), (void *)& token_str))
		return (0);
	j = 0;
	while (j < count)
		token_str[j++] = state->input[i++];
	token_str[j] = '\0';
	add_token_back(&state->token_head, token_str, type);
	free(token_str);
	return (i);
}

void	add_token_back(t_token **head, char *str, int type)
{
	t_token *token;
	int		i;
	int		token_type;
	int		cur_type;
	int		has_space;

	if (type == SINGLE || type == DOUBLE)
		str[ft_strlen(str) - 1] = '\0';
	else if (type == BACKSLASH)
	{
		i = 0;
		str[i] = str[i + 1];
		str[i + 1] = '\0';
	}
	has_space = FALSE;
	if (*head == NULL)
	{
		token_type = check_syntax_error(ERROR_NULL, type, has_space);
		*head = create_token(str, token_type);
	}
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		cur_type = find_cur_type(head, &has_space);
		token_type = check_syntax_error(cur_type, type, has_space);
		token->next = create_token(str, token_type);
	}
}

int		find_cur_type(t_token **head, int *has_space)
{
	t_token	*token;
	int		type;

	token = *head;
	type = token->type;
	while (token)
	{
		if (token->type != SPACE)
			type = token->type;
		else
			*has_space = TRUE;
		token = token->next;
	}
	return type;
}

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
	}
	return (type);
}

t_token	*create_token(char *str, int type)
{
	t_token *token;

	if (!ft_calloc(1, sizeof(t_token), (void *)& token))
		return (0);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}
