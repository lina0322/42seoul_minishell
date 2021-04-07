/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:42:16 by llim              #+#    #+#             */
/*   Updated: 2021/04/07 19:15:54 by llim             ###   ########.fr       */
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

	tputs("----------\n", 0, ft_putchar);
	while (cmd)
	{
		string[0] = '0' + cmd->type;
		tputs(string, 0, ft_putchar);
		tputs("\n", 0, ft_putchar);
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
			if (token->type == SPACE || token->type == PIPE || token->type == SEMICOLON)
				ac--;
			make_cmd(state, start, ac, type);
			if (token->type == PIPE)
				type = PIPE_TYPE;
			else
				type = COLON_TYPE;
			ac = 0;
			start = token->next;
		} else if (token->type == SPACE)
			ac--;
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
			if (start->type == DOUBLE)
				check_env_and_backslash(state, start);
			av[i] = ft_strjoin2(av[i], start->str);
		}
		start = start->next;
	}
	add_cmd_back(&state->cmd_head, av, type);
}

/// todo: 없는 env 터짐(빈값 출력), 큰 따옴표 안에 작은 따옴표.. 처리..! 여러개 들어오는경우ㅠㅠ
void	check_env_and_backslash(t_state *state, t_token *token)
{
	int i;
	char *tmp;
	char *tmp2;
	
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			tmp = find_env_val(state->env_head, &token->str[i + 1]);
			free(token->str);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		else if (token->str[i] == '\\' && token->str[i + 1] == '\\')
		{
			tmp = ft_substr(token->str, 0, i + 1);
			tmp2 = ft_strjoin2(tmp, &token->str[i + 2]);
			free(token->str);
			token->str = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
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
