/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 21:38:10 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:45:26 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rec_nbr(int n, int fd)
{
	if (n >= 10)
		ft_rec_nbr((n / 10), fd);
	write(fd, &"0123456789" [n % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	ft_rec_nbr(n, fd);
}
