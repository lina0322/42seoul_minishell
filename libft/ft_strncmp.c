/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 04:48:10 by dhyeon            #+#    #+#             */
/*   Updated: 2020/07/02 23:01:46 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (t1[i] - t2[i]);
		if (s1[i] == s2[i] && s1[i] == '\0' && s2[i] == '\0')
			return (0);
		else
			i++;
	}
	return (0);
}
