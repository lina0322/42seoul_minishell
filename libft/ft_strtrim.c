/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 06:31:30 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 00:02:28 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		size;
	int		s_len;
	char	*res;

	i = 0;
	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	while (s1[i] != 0 && ft_isset(s1[i], set))
		i++;
	s_len = (ft_strlen(s1)) - 1;
	while (s_len != 0 && ft_isset(s1[s_len], set))
		s_len--;
	if (i >= s_len)
		return (ft_strdup(""));
	size = (s_len - i) + 1;
	if (!ft_calloc(sizeof(char *), size + 1, (void *)& res))
		return (0);
	ft_strlcpy(res, s1 + i, (size + 1));
	return (res);
}
