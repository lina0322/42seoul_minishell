/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:19:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/20 16:11:13 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->av)
			free_2d(tmp->av);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	check_env_space(t_state *state)
{
	t_token	*token;

	token = state->token_head;
	while (token)
	{
		if (!ft_strcmp(token->str, "echo"))
		{
			token = token->next;
			remove_space(token);
		}
		if (token)
			token = token->next;
	}
}

void	remove_space(t_token *token)
{
	char	*temp;

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
	if (!str)
		return (result);
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
	free_2d(strs);
	return (result);
}

int		check_key_len(char *str, int is_tokenizer)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == ' ')
			break ;
		if (is_operator(str, len) && is_tokenizer)
			break ;
		len++;
	}
	return (len);
}
