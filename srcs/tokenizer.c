/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 15:34:10 by llim             ###   ########.fr       */
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
			if (!(count = find_end(state, type, ++i)))
			{
				i = make_token(state, 1, i - 1, ERROR_QUOTE);
				break ;
			}
		i = make_token(state, count, i, type);
	}
	check_token_error(state);
}

int		make_token(t_state *state, int count, int i, int type)
{
	char	*token_str;
	int		j;

	if (!ft_calloc(count + 1, sizeof(char), (void *)& token_str))
		exit(1);
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
	int		token_type;
	int		cur_type;
	int		has_space;

	str = trim_str(str, type);
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

char	*trim_str(char *str, int type)
{
	int	i;

	if (type == SINGLE || type == DOUBLE)
		str[ft_strlen(str) - 1] = '\0';
	else if (type == BACKSLASH)
	{
		i = 0;
		str[i] = str[i + 1];
		str[i + 1] = '\0';
	}
	return (str);
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
	return (type);
}
