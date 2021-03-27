/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/03/24 15:47:08 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// token 확인용 출력구문, 차후 삭제예정
void	print_token(t_state *state)
{
	t_token *token;

	token = state->token_head;
	while (token)
	{
		printf("%s, %i\n", token->str, token->type);
		token = token->next;
	}
}

void	tokenizer(t_state *state)
{
	int		type;
	int		count;
	int		i;

	i = 0;
	while (state->input[i])
	{
		if (!(type = is_operator(state->input[i])))
			count = get_len(state->input, i);
		else if (type == SINGLE || type == DOUBLE)
		{
			if (!(count = find_end(state->input, type, ++i)))
			{
				printf("따옴표 에러\n");
				return ;
			}
		}
		else
			count = 1;
		i = make_token(state, count, i, type);
	}
}

int		make_token(t_state *state, int count, int i, int type)
{
	char	*token_str;
	int		j;

	token_str = malloc(sizeof(char) * count + 1);
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
	int		len;

	if (type == SPACE)
		return ;
	else if (type == SINGLE || type == DOUBLE)
	{
		len = ft_strlen(str);
		str[len - 1] = '\0';
	}
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
