/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:55:05 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 13:01:26 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(t_env *tmp, char *str)
{
	int	klen;
	int	vlen;
	int	i;

	klen = 0;
	vlen = 0;
	while (str[klen] != '=')
		klen++;
	if (!ft_calloc(sizeof(char), klen + 1, (void *)& tmp->key))
		exit(1);
	i = -1;
	while (++i < klen)
		tmp->key[i] = str[i];
	tmp->key[i] = '\0';
	if (str[klen + 1] == '\0')
		return (0);
	while (str[klen + 1 + vlen] != '\0')
		vlen++;
	if (!ft_calloc(sizeof(char), vlen + 1, (void *)& tmp->value))
		exit(1);
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

void	error_export(t_state *s, t_cmd *cmd, int i)
{
	printf("bash: export: `%s': not a valid identifier\n", cmd->av[i]);
	s->ret = 1;
}

void	ft_export(t_state *s, t_cmd *cmd, int i)
{
	t_env	tmp;

	s->ret = 0;
	if (cmd->ac == 1)
		print_export(s->env_head);
	else
	{
		while (++i < cmd->ac)
		{
			if ((cmd->av[i][0] != '_' && !ft_isalpha(cmd->av[i][0]))
				|| !check_key2(cmd->av[i]))
				error_export(s, cmd, i);
			else if (ft_strrchr(cmd->av[i], '=') == 0)
				update_env(s->env_head, cmd->av[i], 0, 0);
			else
			{
				if (parse_export(&tmp, cmd->av[i]) == 0)
					tmp.value = 0;
				update_env(s->env_head, tmp.key, tmp.value, 1);
				free(tmp.key);
				free(tmp.value);
			}
		}
	}
}
