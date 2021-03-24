/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/03/24 15:47:08 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: 스페이스 무시하기, 따옴표 관리하기
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
	return 0;
}

int		get_len(char *input, int i)
{
	int		len;

	len = 0;
	while (input[i])
	{
		if (is_operator(input[i]))
			break;
		i++;
		len++;
	}
	return (len);
}

void	tokenizer(t_state *state)
{
	char	*input;
	int		i;
	char	*token_str;
	int		j;
	int		count;
	int		type;

	input = ft_strdup(state->input);
	i = 0;
	while (input[i])
	{
		j = 0;
		type = is_operator(input[i]);
		if (!type)
		{
			type = COMMON;
			count = get_len(input, i);
			token_str = malloc(sizeof(char *) * count + 1);
			while (j < count)
				token_str[j++] = input[i++];
		} else {
			token_str = malloc(sizeof(char *) * 2);
			token_str[j++] = input[i++];
		}
			token_str[j] = '\0';
			add_token_back(&state->token_head, token_str, type);
			free(token_str);
	}
	// token 확인용 출력구문
	t_token *token = state->token_head;
	while (token)
	{
		printf("%s, %i\n", token->str, token->type);
		token = token->next;
	}
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
