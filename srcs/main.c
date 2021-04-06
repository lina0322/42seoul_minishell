/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/06 06:35:07 by dhyeon           ###   ########.fr       */
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
		prepare_token_and_cmd(&state);
	}
}

void	prepare_token_and_cmd(t_state *state)
{
	free_cmd(state->cmd_head);
	// ft_memset((void *)state->token_head, 0, sizeof(t_token));
	state->token_head = 0;
 	// ft_memset((void *)state->cmd_head, 0, sizeof(t_cmd));
	state->cmd_head = 0;
	free(state->input);
	state->input = 0;
}

void	init_state(t_state *state)
{
	ft_memset((void *)state, 0, sizeof(t_state));
}

void	free_2d(char **array)
{
	char **temp;
	int	i;

	temp = array;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(array);
}
