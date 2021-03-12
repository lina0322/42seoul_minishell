/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 02:59:30 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/02 22:52:42 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	i = 0;
	if (size <= d_len)
		return (s_len + size);
	while (size - 1 > i + d_len && src[i] != '\0')
	{
		dest[i + d_len] = src[i];
		i++;
	}
	dest[i + d_len] = '\0';
	return (s_len + d_len);
}
