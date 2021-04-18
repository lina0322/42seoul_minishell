/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 03:43:24 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 19:36:24 by dhyeon           ###   ########.fr       */
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
