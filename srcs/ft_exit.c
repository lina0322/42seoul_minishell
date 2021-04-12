/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:39:54 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/13 07:52:50 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_state *state, t_cmd *cmd)
{
	(void)state;
	(void)cmd;
	// exit 매개변수 확인하여 인자로 넘기기 추가
	// All Free 함수 구현후 추가
	printf("exit\n");
	exit(0);
}
