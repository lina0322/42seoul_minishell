/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/13 07:01:14 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char *envp[])
{
	t_state	state;

	(void)argc;
	(void)argv;
	init_state(&state);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
	parse_env(envp, &state);
	// parse_path(&state);
	while (1)
	{
		prompt2(&state);
		tcsetattr(0, TCSANOW, &state.t.save);
		tokenizer(&state);
		execute(&state, state.cmd_head, envp);
		prepare_token_and_cmd(&state);
	}
}

void	prepare_token_and_cmd(t_state *state)
{
	free_cmd(state->cmd_head);
	state->token_head = 0;
	state->cmd_head = 0;
	state->path_head = 0;
	free(state->input);
	state->input = 0;
}

void	init_state(t_state *state)
{
	ft_memset((void *)state, 0, sizeof(t_state));
	tcgetattr(0, &state->t.save);
}

void	free_2d(char **array)
{
	char	**temp;
	int		i;

	temp = array;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}
