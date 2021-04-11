/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/08 23:47:26 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_state *state)
{
	t_token	*token;
	t_token *start;
	int		type;
	int		ac;

	token = state->token_head;
	start = state->token_head;
	type = NORMAL_TYPE;
	ac = 0;
	while (token)
	{
		ac++;
		if (token->type == ERROR_QUOTE)
		{
			make_cmd(state, start, ac, ERROR_QUOTE);
			break;
		}
		else if (token->type == PIPE || token->type == SEMICOLON || !token->next)
		{
			if (token->type == SPACE || token->type == PIPE || token->type == SEMICOLON)
				ac--;
			make_cmd(state, start, ac, type);
			if (token->type == PIPE)
				type = PIPE_TYPE;
			else
				type = COLON_TYPE;
			ac = 0;
			start = token->next;
		} 
		else if (token->type == SPACE)
			ac--;
		if (token)
			token = token->next;
	}
	free_token(state->token_head);
}

void	make_cmd(t_state *state, t_token *start, int ac, int type)
{
	char	**av;
	int		i;

    if (!ft_calloc(ac + 1, sizeof(char *), (void **)& av))
	    return ;
	i = ac + 1;
	while (i > 0)
		av[--i] = 0;
	while (start && i < ac && start->type != PIPE && start->type != SEMICOLON)
	{
		if (start->type == SPACE)
		{
			if (av[i])
				i++;
		}
		else
		{
			if (start->type == DOUBLE || start->type == COMMON)
			{
				check_backslash(start);
				check_env(state, start);
			}
			av[i] = ft_strjoin2(av[i], start->str);
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, type);
}

void	check_backslash(t_token *token)
{
	int i;
	char *tmp;
	char *tmp2;
	
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\\' && 
		(token->str[i + 1] == '\\' || token->str[i + 1] == '\"'))
		{
			tmp = ft_substr(token->str, 0, i);
			tmp2 = ft_strjoin2(tmp, &token->str[i + 1]);
			free(token->str);
			token->str = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
		}
		i++;
	}
}

void	check_env(t_state *state, t_token *token)
{
	int i;
	int j;
	char *value;
	char *temp;
	char *temp2;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && token->str[i + 1])
		{
			j = i + 1;
			while (token->str[j])
			{
				if (token->str[j] == '\'' || token->str[j] == ' ')
					break;
				j++;
			}
			temp = ft_substr(token->str, i + 1, j - 1 - i); // key
			if (!ft_strcmp(temp, "?"))
			{
				i++;
				continue;
			}
			value = ft_strdup(find_env_val(state->env_head, temp));
			free(temp);
			temp = ft_substr(token->str, 0, i); // $이전 str
			temp2 = ft_strjoin2(temp, value); // $이전 str에 value 합침
			temp = ft_substr(token->str, j, ft_strlen(token->str)); // 환경변수 이후 str
			free(token->str);
			token->str = ft_strjoin2(temp2, temp); // $이전 str에 value합친거 뒤에 환경변수 이후 str까지 더함
			free(value);
			free(temp2);
			free(temp);
		}
		i++;
	}
}

void	add_cmd_back(t_cmd **head, char **av, int type)
{
	t_cmd	*cmd;
	int		ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (*head == NULL)
		*head = create_cmd(av, ac, type, 0);
	else
	{
		cmd = *head;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = create_cmd(av, ac, type, cmd);
	}
}

t_cmd	*create_cmd(char **av, int ac, int type, t_cmd *prev)
{
	t_cmd *cmd;

	if (av == NULL)
		return NULL;
    if (!ft_calloc(1, sizeof(t_cmd), (void *)& cmd))
	    return (NULL);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	cmd->next = 0;
	cmd->prev = prev;
	return (cmd);
}

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
