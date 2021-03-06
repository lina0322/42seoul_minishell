/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/19 21:39:57 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char *envp[])
{
	(void)argc;
	(void)argv;
	print_mini();
	init_state(&g_state);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
	parse_env(envp, &g_state);
	while (1)
	{
		prompt2(&g_state);
		tcsetattr(0, TCSANOW, &g_state.t.save);
		tokenizer(0, 1);
		execute(&g_state, g_state.cmd_head, envp);
		prepare_token_and_cmd(&g_state);
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
	free(state->input2);
	state->input2 = 0;
	reset_save(state);
}

void	init_state(t_state *state)
{
	ft_memset((void *)state, 0, sizeof(t_state));
	tcgetattr(0, &state->t.save);
}

void	jump_space(char *str, int *i)
{
	if (str)
		*i = *i + 1;
}
