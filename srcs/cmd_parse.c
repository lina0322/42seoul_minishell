/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/04 13:44:13 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///for test
void	print_cmd(t_state *state)
{
	t_cmd	*cmd = state->cmd_head;
	int		i = 0;

	while (cmd)
	{
		while (i < cmd->ac)
		{
			tputs(cmd->av[i], 0, ft_putchar);
			tputs(" ", 0, ft_putchar);
			i++;
		}
		cmd = cmd->next;
		tputs("\n", 0, ft_putchar);
	}
}

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
		if (token->type == PIPE || token->type == SEMICOLON || !token->next)
		{
			ac++;
			make_cmd(state, start, ac, type);
			if (token->type == PIPE)
				type = PIPE_TYPE;
			else
				type = COLON_TYPE;
			ac = 0;
			token = token->next;
		}
		else
		{
			if (token->type != SPACE)
				ac++;
		}
		if (token)
			token = token->next;
	}
	print_cmd(state);
	free_token(state->token_head);
}

void	make_cmd(t_state *state, t_token *start, int ac, int type)
{
	char	**av;
	int		i;

	av = (char **)malloc(sizeof(char *) * ac + 1);
	if (!av)
		return;
	i = 0;
	while (i < ac)
		av[i++] = 0;
	i = 0;
	while (start && i < ac)
	{
		if (start->type == SPACE || start->type == PIPE || start->type == SEMICOLON)
			i++;
		else
		{
			// todo: type == DOUBLE일ㄸㅐ $처리!
			av[i] = ft_strjoin2(av[i], start->str);
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, ac, type);
}

void	add_cmd_back(t_cmd **head, char **av, int ac, int type)
{
	t_cmd	*cmd;

	if (*head == NULL)
		*head = create_cmd(av, ac, type);
	else
	{
		cmd = *head;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = create_cmd(av, ac, type);
	}
}

t_cmd	*create_cmd(char **av, int ac, int type)
{
	t_cmd *cmd;

	if (av == NULL)
		return NULL;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (0);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	// cmd->pip
	cmd->next = 0;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		tmp = cmd;
		if (cmd->av)
			free(cmd->av);
		cmd = cmd->next;
		free(tmp);
	}
}
