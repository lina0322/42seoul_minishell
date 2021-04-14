/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:33:51 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/14 22:09:06 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_save	*create_save(char *input, t_save *next, int flag)
{
	t_save *new;

	if (!ft_calloc(1, sizeof(t_save), (void *)& new))
		return (0); //exit
	if (input)
	{
		// printf("create_save input ; %s \n", input);
	}
	new->input = ft_strdup(input);
	if (new->input == 0)
		return (0); //exit
	new->next = next;
	new->prev = 0;
	new->flag = flag;
	return (new);
}

void	save_history(t_state *s)
{
	t_save *tmp;

	if (s->input == 0)
		return ;
	if (s->save_head == 0)
	{
		s->save_head = create_save(s->input, 0, 1);
	}
	else
	{
		tmp = create_save(s->input, s->save_head, 1);
		s->save_head = tmp;
	}
	// printf("save : %s\n", s->save_head->input);
}