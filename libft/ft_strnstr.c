/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 04:23:24 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:47:07 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sfind(const char *s, const char *f, size_t s_pos, size_t n)
{
	size_t	f_pos;

	f_pos = 0;
	while (f[f_pos] != '\0')
	{
		if (s[s_pos] != f[f_pos] || s_pos > n)
			return (0);
		s_pos++;
		f_pos++;
	}
	return (1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	s_len;
	size_t	t_len;
	size_t	i;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	s_len = ft_strlen(str);
	t_len = ft_strlen(to_find);
	if (s_len < t_len || n < t_len)
		return (0);
	while (i < n && str[i] != 0)
	{
		if (str[i] == to_find[0])
		{
			if (sfind(str, to_find, i, n))
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
