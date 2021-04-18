/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 03:43:24 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 19:39:51 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **array)
{
	char	**temp;
	int		i;

	temp = array;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
