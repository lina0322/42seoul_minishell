/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 00:11:54 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char *envp[])
{
	t_state	state;

	init_state(&state);
	parse_env(envp, &state);
	// signal
	// prompt(&state);
	// tokenizer(&state);
}

void	init_state(t_state *state)
{
	state->token_head = 0;
	state->env_head = 0;
	state->input = 0;
}
