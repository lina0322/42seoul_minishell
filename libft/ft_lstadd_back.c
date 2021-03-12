/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 00:20:55 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:29:17 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	new->next = 0;
	tmp->next = new;
}
