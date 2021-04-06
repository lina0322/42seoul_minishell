/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/06 06:08:44 by dhyeon           ###   ########.fr       */
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
		if (token->type == PIPE || token->type == SEMICOLON || !token->next)
		{
			make_cmd(state, start, ac, type);
			if (token->type == PIPE)
				type = PIPE_TYPE;
			else
				type = COLON_TYPE;
			ac = 0;
		}
		if (token)
			token = token->next;
	}
	print_cmd(state);
	// free_token(state->token_head);
}

void	make_cmd(t_state *state, t_token *start, int ac, int type)
{
	char	**av;
	int		i;

    if (!ft_calloc(ac + 1, sizeof(char **), (void **)& av))
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
			// todo: type == DOUBLE일ㄸㅐ $처리, 따옴표 종류들 \처리
			if (start->type == DOUBLE)
				// check_env(start);
			if (start->type == SINGLE || start->type == DOUBLE)
				// check_backslass
			av[i] = ft_strjoin2(av[i], start->str);
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, ac, type);
}

// void	check_env(t_token *token)
// {
// 	int i
// 	while
// 	token->str
// }

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
    if (!ft_calloc(1, sizeof(t_cmd), (void *)& cmd))
	    return (NULL);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	// cmd->pip
	cmd->next = 0;
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
