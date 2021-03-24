/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:55:05 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/24 15:53:27 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(t_env *tmp, char *str)
{
	int	klen;
	int vlen;
	int	i;

	klen = 0;
	vlen = 0;
	while (str[klen] != '=')
		klen++;
	if (!ft_calloc(sizeof(char *), klen + 1, (void *)& tmp->key))
		return (0);
	// tmp->key = (char *)malloc(sizeof(char) * (klen + 1));
	while (str[klen + 1 + vlen] != '\0')
		vlen++;
	if (!ft_calloc(sizeof(char *), vlen + 1, (void *)& tmp->value))
		return (0);
	// tmp->value = (char *)malloc(sizeof(char) * (vlen + 1));
	i = -1;
	while (++i < klen)
		tmp->key[i] = str[i];
	tmp->key[i] = '\0';
	i = -1;
	while (++i < vlen)
		tmp->value[i] = str[i + klen + 1];
	tmp->value[i] = '\0';
	return (1);
}

void	ft_export(t_state *state, t_cmd *cmd)
{
	(void)cmd;
	// //test 1
	// int ac = 4;
	// char *av[] = {"export", "TEST", "=", "123", "0"};
	//test 2
	int ac = 2;
	char *av[] = {"export", "TEST2=456", "0"};
	t_env tmp;

	if (ac == 1) // cmd->ac
		print_export(state->env_head);
	else
	{
		if (ac == 2) // cmd->ac
		{
			// tmp.key = 0;
			// tmp.value = 0;
			parse_export(&tmp, av[1]); // = 없는것 체크해야함
			add_env_back(&state->env_head, tmp.key, tmp.value, 1); // cmd->av
		}
		// else if (ac == 3)
		// {
		// 	//나중에 추가 -> has_equal = 0
		// }
		// else
		// {
		// 	add_env_back(&state->env_head, av[1], av[3], 1); // cmd->av
		// }
	}
}
