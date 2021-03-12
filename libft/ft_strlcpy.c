/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 04:34:13 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:45:50 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	srclen;

	srclen = 0;
	if (dest == 0 || src == 0)
		return (0);
	while (src[srclen] != '\0')
		srclen++;
	i = 0;
	if (size == 0)
		return (srclen);
	while (i < size - 1)
	{
		if (src[i] == '\0')
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}
