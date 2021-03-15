/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/16 01:09:35 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\b\b \nbash> ");
	}
	else if (signo == SIGQUIT)
	{
		printf("\b\b");
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_state	state;

	(void)argc;
	(void)argv;
	(void)envp;
	// if (argc > 10)
	// 	return 0;
//	if (argv[0][1] == '1')
//		return 0;
	init_state(&state);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
	parse_env(envp, &state);
	while (1)
	{
		prompt(&state);
		builtin(&state, state.cmd); // 임시파일
		free(state.input);
		// tokenizer(&state);
	}

	//test
//	print_env_all(state.env_head);
//	print_export(state.env_head);
	// print_one_export(state.env_head, argv[1]);
	// update_env(state.env_head, argv[1], argv[2]);
	// print_one_export(state.env_head, argv[1]);
}

void	init_state(t_state *state)
{
	state->token_head = 0;
	state->env_head = 0;
	state->input = 0;
}
