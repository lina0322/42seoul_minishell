/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/04 12:10:56 by llim             ###   ########.fr       */
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
	 	builtin(&state, state.cmd_head); // 임시파일
		tokenizer(&state);
		free_cmds(state.cmd_head);
		ft_memset((void *)&state.token_head, 0, sizeof(t_token));
 		ft_memset((void *)&state.cmd_head, 0, sizeof(t_cmd));
	}
}

void	init_state(t_state *state)
{
	ft_memset((void *)state, 0, sizeof(t_state));
}
