/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/03/18 22:24:09 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_state *state)
{
	char	*input;
	int		i;
	int		type;

	input = ft_strdup(state->input);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			type = 2;
		else if (input[i] == '\"')
			type = 3;
		else if (is_operator(input[i]))
			add_operator_token(state, &input[i]);
		i++;
	}

	t_token	*token = state->token_head;
	while (token)
	{
		printf("%s, %i\n", token->str, token->type);
		token = token->next;
	}
}

int		is_operator(char c)
{
	if (c == '<' || c == ';' || c == '|' || c == '>' || c == '>')
		return (TRUE);
	else
		return (FALSE);
}

int		add_operator_token(t_state *state, char *c)
{
	int type;

	if (*c == '<')
		type = 4;
	else if (*c == ';')
		type = 7;
	else if (*c == '|')
		type = 8;
	else if (*c == '>')
	{
		if (*c == '>')
		{
			add_token_back(&state->token_head, c, 6);
			return (TRUE);
		}
		type = 5;
	}
	else
		return (FALSE);
	add_token_back(&state->token_head, c, type);
	return (TRUE);
}

void	add_token_back(t_token **head, char *str, int type)
{
	t_token *token;

	if (*head == NULL)
		*head = create_token(str, type);
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		token->next = create_token(str, type);
	}
}

t_token	*create_token(char *str, int type)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}
