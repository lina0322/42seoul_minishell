/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:55:05 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/15 03:35:01 by dhyeon           ###   ########seoul.kr  */
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
	if (!ft_calloc(sizeof(char), klen + 1, (void *)& tmp->key))
		return (0); // 말록실패는 exit처리
	i = -1;
	while (++i < klen)
		tmp->key[i] = str[i];
	tmp->key[i] = '\0';
	if (str[klen + 1] == '\0')
		return (0);
	while (str[klen + 1 + vlen] != '\0')
		vlen++;
	if (!ft_calloc(sizeof(char), vlen + 1, (void *)& tmp->value))
		return (0);
	i = -1;
	while (++i < vlen)
		tmp->value[i] = str[i + klen + 1];
	tmp->value[i] = '\0';
	return (1);
}

int	check_key2(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0' && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_state *s, t_cmd *cmd)
{
	int	i;
	t_env tmp;

	if (cmd->ac == 1) // cmd->ac
		print_export(s->env_head);
	else
	{
		i = 1;
		while (i < cmd->ac)
		{
			if ((cmd->av[i][0] != '_' && !ft_isalpha(cmd->av[i][0]))
										|| !check_key2(cmd->av[i]))
				printf("bash: export: `%s': not a valid identifier\n", cmd->av[i]);
			else if (ft_strrchr(cmd->av[i], '=') == 0) // = 이 없는경우 (1. key값만 있는경우)
				update_env(s->env_head, cmd->av[i], 0, 0);
			else // = 가 있는 경우
			{
				if (parse_export(&tmp, cmd->av[i]) == 0) // value 값이 없는 경우 value = 0 으로
					tmp.value = 0;
				update_env(s->env_head, tmp.key, tmp.value, 1);
				free(tmp.key);
				free(tmp.value);
			}
			i++;
		}
	}
}
