/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:33:51 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 13:02:10 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_save(t_save *save)
{
	if (save->prev != 0)
		save->prev->next = save->next;
	if (save->next != 0)
		save->next->prev = save->prev;
	free(save->input);
	free(save);
	save = 0;
}

void	reset_save(t_state *s)
{
	t_save	*tmp;

	if (s->save_head == 0)
		return ;
	while (s->save_head->prev)
		s->save_head = s->save_head->prev;
	tmp = s->save_head->next;
	if (s->save_head->flag == 0)
	{
		delete_save(s->save_head);
		s->save_head = tmp;
	}
	s->s_flag = 0;
}

t_save	*push_front_save(char *input, t_save *old_head, int flag)
{
	t_save	*new;

	new = 0;
	if (!ft_calloc(1, sizeof(t_save), (void *)& new))
		exit(1);
	new->input = ft_strdup(input);
	new->prev = 0;
	new->next = old_head;
	new->flag = flag;
	if (old_head != 0)
		old_head->prev = new;
	return (new);
}

void	save_history(t_state *s)
{
	reset_save(s);
	if (s->input == 0)
		return ;
	if (s->save_head == 0)
	{
		s->save_head = push_front_save(s->input, 0, 1);
	}
	else
	{
		s->save_head = push_front_save(s->input, s->save_head, 1);
	}
}
