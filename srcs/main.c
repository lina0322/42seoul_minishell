/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/15 17:30:53 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char *envp[])
{
	t_state	state;

	if (argc > 10)
		return 0;
	if (argv[0][1] == '1')
		return 0;
	init_state(&state);
	parse_env(envp, &state);
	// signal
	// prompt(&state);
	// tokenizer(&state);

	//test
//	print_env_all(state.env_head);
//	print_export_all(state.env_head);
//	 print_export_sorted_list(state.env_head);
}

void	init_state(t_state *state)
{
	state->token_head = 0;
	state->env_head = 0;
	state->input = 0;
}
