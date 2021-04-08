/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:22:35 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/08 06:23:44 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*ft_strcjoin(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		if (!ft_calloc(2, sizeof(char *), (void *)& ret))
			return (0); // exit 처리
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		if (!ft_calloc(ft_strlen(str) + 2, sizeof(char *), (void *)& ret))
			return (0); // exit 처리
		i = -1;
		while (str[++i])
			ret[i] = str[i];
		ret[i] = c;
		ret[i + 1] = '\0';
		free(str);
	}
	return (ret);
}

void	print_save_char(t_state *s, char c)
{
	s->input = ft_strcjoin(s->input, c);
	write(1, &c, 1);
}

char	*delete_last_char(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!ft_calloc(len, sizeof(char *), (void *)& tmp))
		return (0); //exit 처리
	i = 0;
	while (str[i + 1])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len] = '\0';
	free(str);
	str = tmp;
	return (str);
}
