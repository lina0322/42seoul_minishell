/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 02:00:20 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/31 17:52:21 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *av[] = {"ls", "-al", 0}; //

void	make_path(t_cmd *cmd, char *str)
{
	char	*tmp;
	char	*tmp2;

	(void)cmd;
	tmp = av[0];
	tmp2 = ft_strjoin(str, "/");
	if (!tmp2)
		return ; //exit
	av[0] = ft_strjoin(tmp2, av[0]);
	if (!av[0])
		return ; //exit
	printf("%s\n", av[0]);
	// free(tmp);
	// free(tmp2);
}

int		find_command(t_state *s, t_cmd *cmd) // 찾으면 1 못찾으면 0
{
	(void)s;
	(void)cmd;
	//test
	// char *paths[] = {"/home/dhyeon/.local/bin", "/home/dhyeon/.rbenv/shims", "/home/dhyeon/.rbenv/bin", "/usr/local/sbin", "/usr/local/bin",
	// 			"/usr/sbin", "/usr/bin", "/sbin", "/bin", "/usr/games", "/usr/local/games", "/snap/bin", 0};
	char *paths[] = {"/Users/dhyeon/.brew/bin", "/usr/local/bin", "/usr/bin", "/bin", "/usr/sbin", "/sbin", "/usr/local/munki", 0};
	int i = 0;
	DIR				*dir_ptr;
	struct dirent	*file;
	char			*tmp;
	(void)tmp;

	while (paths[i]) // 나중엔 링크드리스트로 수정
	{
		dir_ptr = opendir(paths[i]);
		while (dir_ptr)
		{
			file = readdir(dir_ptr);
			if (file == 0)
				break ;
			if (!ft_strcmp(av[0], file->d_name))
			{
				make_path(cmd, paths[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int		builtin(t_state *s, t_cmd *cmd)
{
	//test용
	(void)cmd;

	if (!ft_strcmp(s->input, "pwd")) // 나중에 input 대신 cmd의 명령어로 수정해야함
		ft_pwd(s, cmd);
	else if (!ft_strcmp(s->input, "echo"))
		ft_echo(s, cmd);
	else if (!ft_strcmp(s->input, "cd"))
		ft_cd(s, cmd);
	else if (!ft_strcmp(s->input, "env"))
		print_env_all(s->env_head);
	else if (!ft_strcmp(s->input, "export"))
		ft_export(s, cmd);
	else if (!ft_strcmp(s->input, "unset"))
		ft_unset(s, cmd);
	else if (!ft_strcmp(s->input, "exit"))
		ft_exit(s, cmd);
	else if (!ft_strcmp(s->input, "test"))
		find_command(s, cmd);
	return (0);
}

void	parse_cmd(t_cmd **head)
{
	t_cmd	*cmd;
	
	while (cmd)
	{

		cmd = cmd->next;
	}
}

void	add_cmd_back(t_cmd **head, char **av, int ac, int type)
{
	t_cmd	*cmd;

	if (*head == NULL)
		*head = create_cmd(av, ac, type);
	else
	{
		cmd = *head;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = create_cmd(av, ac, type);
	}
}

t_cmd	*create_cmd(char **av, int ac, int type)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (0);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	// cmd->pip
	cmd->next = 0;
	return (cmd);
}
