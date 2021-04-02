/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/03 00:37:35 by llim             ###   ########.fr       */
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
	parse_path(&state);
	while (1)
	{
	 	prompt(&state);
	// 	builtin(&state, state.cmd_head); // 임시파일
	 	tokenizer(&state);
		state.token_head = 0;
	// 	parse_cmd(&state);
	}
}

void	init_state(t_state *state)
{
	state->token_head = 0;
	state->env_head = 0;
	state->input = 0;
	state->ret = 0;
}
