/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 01:34:16 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:43:49 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lstnew_protect(void *content, t_list **tmp)
{
	tmp = ft_lstnew(content);
	if (!tmp)
		return (0);
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;
	t_list	*new;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	if (!lstnew_protect(f(lst->content), &res))
		return (0);
	tmp = res;
	lst = lst->next;
	while (lst)
	{
		if (!lstnew_protect(f(lst->content), &new))
		{
			ft_lstclear(&res, del);
			return (0);
		}
		tmp->next = new;
		tmp = tmp->next;
		lst = lst->next;
	}
	return (res);
}
