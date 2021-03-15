/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:52:08 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/16 02:24:51 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_state *s, char *path)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(find_env_val(s->env_head, "HOME")); //나중에 말록프로텍트해주자
	else
		buf = ft_strdup(path);
	ret = chdir(buf);
	return (ret);
}

int	ft_cd(t_state *s, t_cmd *cmd)
{
	char	*test[] = {"cd", "..", 0};
	char	pwd[999];

	(void)cmd;
	// if (cmd->argc == 1)
	// 	change_dir(s, "~"); // cd만 입력했을 경우 home으로 이동하도록하는 함수 / 주석풀고는 밑에 else 추가
	if (change_dir(s, test[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", test[1]); // test수정 + 리턴 코드 수정
	}
	else
	{
		getcwd(pwd, 999);
		update_env(s->env_head, "OLDPWD", find_env_val(s->env_head, "PWD"));
		update_env(s->env_head, "PWD", pwd); // test 는 나중에 수정 + 리턴 코드 수정
	}
	return (0);
}
