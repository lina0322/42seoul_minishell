/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/13 23:48:02 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///for test
void	print_cmd(t_state *state)
{
	t_cmd	*cmd = state->cmd_head;
	int		i = 0;
	char string[2];
	string[1] = 0;
	
	while (cmd)
	{
		string[0] = '0' + cmd->type;
		tputs(string, 0, ft_putchar);
		while (i < cmd->ac)
		{
			tputs(cmd->av[i], 0, ft_putchar);
			tputs(",", 0, ft_putchar);
			
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
	print_cmd(state);
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
				check_backslash_and_env(state, start);
			av[i] = ft_strjoin2(av[i], start->str);
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, type);
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
