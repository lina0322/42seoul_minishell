/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/18 14:42:23 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_state *state, int ac)
{
	t_token	*token;
	t_token *start;
	int		type;

	token = state->token_head;
	start = state->token_head;
	type = NORMAL_TYPE;
	while (token)
	{
		ac++;
		if (token->type >= PIPE || !token->next)
		{
			if (token->type == SPACE || token->type >= PIPE)
				ac--;
			make_cmd(state, start, ac, type);
			if (token->type >= PIPE)
				type = token->type;
			ac = 0;
			start = token->next;
		}
		else if (token->type == SPACE)
			ac--;
		token = token->next;
	}
}

void	make_cmd(t_state *state, t_token *start, int ac, int type)
{
	char	**av;
	char	*tmp;
	int		i;

	if (!ft_calloc(ac + 1, sizeof(char *), (void **)& av))
		exit(1);
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
			tmp = make_av(state, start, av[i]);
			free(av[i]);
			av[i] = tmp;
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, type);
}

char	*make_av(t_state *state, t_token *start, char *str)
{
	char	*tmp;

	if (start->type == DOUBLE || start->type == COMMON)
		check_backslash_and_env(state, start);
	tmp = ft_strjoin2(str, start->str);
	return (tmp);
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
		return (NULL);
	if (!ft_calloc(1, sizeof(t_cmd), (void *)& cmd))
		exit(1);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	cmd->next = 0;
	cmd->prev = prev;
	return (cmd);
}
