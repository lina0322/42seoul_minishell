/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:33:51 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/17 03:38:19 by dhyeon           ###   ########seoul.kr  */
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
}

void	reset_save(t_state *s)
{
	if (s->save_head == 0)
		return ;
	while (s->save_head->prev)
	{
		if (s->save_head->flag == 0)
			delete_save(s->save_head);
		s->save_head = s->save_head->prev;
	}
	if (s->save_head->flag == 0)
			delete_save(s->save_head);
	s->s_flag = 0;
}

t_save	*push_front_save(char *input, t_save *old_head, int flag)
{
	t_save	*new;

	if (!ft_calloc(1, sizeof(t_save), (void *)& new))
		return (0); //exit
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
	// printf("save : %s\n", s->save_head->input);
}
