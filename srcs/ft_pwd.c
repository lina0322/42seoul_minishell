/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:52:39 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/30 19:45:02 by dhyeon           ###   ########.fr       */
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
		printf("%s\n", buf);
	return (0);
}
