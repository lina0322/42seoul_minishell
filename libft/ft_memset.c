/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 04:36:15 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/01 23:03:31 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t n)
{
	unsigned char	*tmp_ptr;
	unsigned char	tmp_val;
	size_t			i;

	tmp_ptr = ptr;
	tmp_val = val;
	i = 0;
	while (i < n)
	{
		tmp_ptr[i] = tmp_val;
		i++;
	}
	return (ptr);
}
