/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:52:05 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/02 01:51:00 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;

	if (dest == src || n == 0)
		return (dest);
	dest_tmp = dest;
	src_tmp = (unsigned char *)src;
	if (dest < src)
	{
		while (n--)
			*dest_tmp++ = *src_tmp++;
	}
	else
	{
		dest_tmp += (n - 1);
		src_tmp += (n - 1);
		while (n--)
			*dest_tmp-- = *src_tmp--;
	}
	return (dest);
}
