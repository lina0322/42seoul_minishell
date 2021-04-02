/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 02:00:20 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/03 00:19:45 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///for test
void	print_cmd(t_state *state)
{
	t_cmd	*cmd = state->cmd_head;
	int i = 0;
	int count = cmd->ac;

	while (cmd)
	{
		printf("type %d\n", cmd->type);
		while (i < count)
		{
			printf("av[%i] %s, ", i, cmd->av[i]);
			i++;
		}
		cmd = cmd->next;
		printf("\n");
	}		
}

char *av[] = {"ls", "-al", 0}; //

void	make_path(t_cmd *cmd, char *str)
{
	char	*tmp;
	char	*tmp2;

	(void)cmd;
	(void)tmp;
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
	// else if (!ft_strcmp(s->input, "test"))
	// 	find_command(s, cmd);
	return (0);
}

void	parse_cmd(t_state *state)
{
	t_token	*token;
	int		type;
	int		ac;
	
	token = state->token_head;
	type = NORMAL_TYPE;
	ac = 0;
	while (token)
	{
		if (token->type == PIPE || token->type == SEMICOLON)
		{
			make_av(state, ac, type);
			if (token->type == PIPE)
				type = PIPE_TYPE;
			else
				type = COLON_TYPE;
			ac = 0;
		} 
		else
			ac++;
		token = token->next;
	}
	make_av(state, ac, type);
	free_tokens(token);	
	print_cmd(state);
}

void	make_av(t_state *state, int ac, int type)
{
	t_token	*token;
	t_token	*temp;
	char	**av;
	int		i;

	if (state->token_head == NULL) 
		return ;
	token = state->token_head;
	av = 0;
	if (ac != 0)
	{
		i = 0;
		av = (char **)malloc(sizeof(char *) * ac + 1);
		if (!av)
		while (i < ac)
		{
			av[i++] = ft_strdup(token->str);
			temp = token;
			token = token->next;
			state->token_head = token;
			free_token(temp);
		}
		av[i] = 0;
	}
	temp = token;
	token = token->next;
	state->token_head = token;
	free_token(temp);
	return (add_cmd_back(&state->cmd_head, av, ac, type));
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

	if (av == NULL)
		return NULL;
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
