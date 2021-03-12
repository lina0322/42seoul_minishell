/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 04:55:26 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:27:50 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_i(const char *str, int min, long long res, int i)
{
	long long	tmp;

	tmp = 0;
	while (str[i] != 0 && ('0' <= str[i] && str[i] <= '9'))
	{
		if (min > 0 && tmp < 0)
			return (-1);
		if (min < 0 && tmp < 0)
			return (0);
		tmp = (tmp * 10) + (str[i] - 48);
		i++;
		if (str[i] == 0 || !('0' <= str[i] && str[i] <= '9'))
			return (tmp * min);
	}
	if (min == -1)
		res = tmp * -1;
	return (res);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				min;
	long long int	res;

	i = 0;
	min = 1;
	res = 0;
	while (str[i] != 0 && (str[i] == ' ' || (9 <= str[i] && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		min = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = print_i(str, min, res, i);
	return (res);
}
