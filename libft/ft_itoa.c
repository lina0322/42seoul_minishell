/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 09:53:35 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 00:01:54 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_to_num(char *res, int n, int i)
{
	long long	nbr;
	int			j;

	nbr = n;
	j = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		res[j++] = '-';
	}
	while (i >= j)
	{
		res[i] = (nbr % 10) + 48;
		nbr /= 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long long	tmp;

	i = 0;
	tmp = n;
	if (n < 0)
	{
		i++;
		tmp *= -1;
	}
	while (tmp > 0)
	{
		tmp /= 10;
		i++;
	}
	if (n == 0)
		i = 1;
	if (!ft_calloc(sizeof(char *), i + 1, (void *)& res))
		return (0);
	res = ft_to_num(res, n, (i - 1));
	res[i] = '\0';
	return (res);
}
