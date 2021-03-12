/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 08:12:58 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 00:01:32 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_cnt(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != 0 && s[i] != c)
		{
			cnt++;
			while (s[i] != 0 && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

int	ft_get_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			break ;
		i++;
		len++;
	}
	return (len);
}

char	**ft_all_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

char	**ft_put_str(char **res, char const *s, char c)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	k = 0;
	while (s[k] != 0)
	{
		if (s[k] != c)
		{
			len = ft_get_len(s, c, k);
			if (!ft_calloc(sizeof(char *), len + 1, (void *)& res[i]))
				return (ft_all_free(res));
			j = 0;
			while (j < len)
				res[i][j++] = s[k++];
			res[i][j] = '\0';
			i++;
		}
		else
			k++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		n;

	if (s == 0)
		return (0);
	n = ft_str_cnt(s, c);
	if (!ft_calloc(sizeof(char **), n + 1, (void **)& res))
		return (0);
	res = ft_put_str(res, s, c);
	if (res == 0)
		return (0);
	return (res);
}
