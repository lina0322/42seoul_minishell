/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 03:51:25 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/02 04:36:04 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	tmp;
	int				i;

	tmp = c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == tmp)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
