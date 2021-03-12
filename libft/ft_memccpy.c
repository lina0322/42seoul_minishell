/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:13:01 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/01 20:20:23 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;
	unsigned char	c_tmp;
	size_t			i;

	dest_tmp = dest;
	src_tmp = (unsigned char *)src;
	c_tmp = c;
	i = 0;
	while (i < n)
	{
		dest_tmp[i] = src_tmp[i];
		if (src_tmp[i] == c_tmp)
			return (dest + (i + 1));
		i++;
	}
	return (0);
}
