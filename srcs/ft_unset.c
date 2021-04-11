/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:12:15 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/11 17:35:21 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	delete_env(t_env *head, char *key)
{
	t_env	*env;
	t_env	*pre;

	env = head;
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
		{
			pre->next = env->next;
			free_one_env(env);
			return ;
		}
		else
			pre = env;
		env = env->next;
	}
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_state *s, t_cmd *cmd)
{
	int		i;
	// //test
	// char	*av[] = {"unset", "TEST", "!test", 0};
	// int		ac = 3;

	// (void)s;
	// (void)cmd;
	// add_env_back(&s->env_head, "TEST", "123", 1);
	// add_env_back(&s->env_head, "TEST2", "456", 1);
	// add_env_back(&s->env_head, "TEST3", "456", 1);
	// print_env_all(s->env_head);
	// printf("=============================\n"); //

	if (cmd->ac > 1)
	{
		i = 1;
		while (i < cmd->ac)
		{
			if (!check_key(cmd->av[i]))
				printf("bash: unset: `%s': not a valid identifier\n", cmd->av[i]);
			else
				delete_env(s->env_head, cmd->av[i]);
			i++;
		}
	}
}
