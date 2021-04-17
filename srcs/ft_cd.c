/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:52:08 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 01:02:53 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_state *s, char *path)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(find_env_val(s->env_head, "HOME"));
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(find_env_val(s->env_head, "OLDPWD"));
	else
		buf = ft_strdup(path);
	if (!buf)
		exit (1);
	ret = chdir(buf);
	free(buf);
	return (ret);
}

int	ft_cd(t_state *s, t_cmd *cmd)
{
	char	pwd[999];

	(void)cmd;
	if (cmd->ac == 1)
		change_dir(s, "~");
	else if (change_dir(s, cmd->av[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->av[1]);
		s->ret = 1;
	}
	else
	{
		getcwd(pwd, 999);
		update_env(s->env_head, "OLDPWD", find_env_val(s->env_head, "PWD"), 1);
		update_env(s->env_head, "PWD", pwd, 1);
		s->ret = 0;
	}
	return (0);
}
