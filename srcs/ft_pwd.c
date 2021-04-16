/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:52:39 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/17 06:31:21 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_state *s, t_cmd *cmd)
{
	char	buf[999];

	(void)cmd;
	(void)s;
	if (!getcwd(buf, 999))
		return (-1); //에러처리
	else
	{
		printf("%s\n", buf);
		s->ret = 0;
	}
	return (0);
}
