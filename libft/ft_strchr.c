/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 03:09:20 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/03 03:59:57 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	tmp;
	size_t			i;

	tmp = c;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == tmp)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == tmp)
		return ((char *)(str + i));
	return (0);
}
