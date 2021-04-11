/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:32 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/11 17:31:24 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_state *s, t_cmd *cmd)
{
	if (!builtin(s, cmd)) // builtin 아닐때
	{
		if (!find_command(s, cmd)) // 패스 함수도 아닐때!
		{
			if (s->input)
				printf("bash: %s: command not found\n", s->input); //cmd->av[0]로 수정, 문자일때만 처리, 아닐땐 무시
		}
		else //패스함수일때!
		{

		}
	}
	//history 저장 input 그대로 저장하면 됨
}

// int	check_multiline_quote(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	while (tmp)
// 	{
// 		if (tmp->type == -1)
// 			return (0);
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

// void	set_pipe(t_cmd *cmd)
// {
// 	if (cmd->type == PIPE_TYPE || cmd->next->type == PIPE_TYPE)
// 	{
// 		pipe(cmd->pip);
// 		if (cmd->type != PIPE_TYPE)
// 			dup2(cmd->pip[1], 1);
// 		else if (cmd->next == 0 || cmd->type == COLON_TYPE)
// 			dup2(cmd->prev->pip[0], 0);
// 		else
// 		{
// 			dup2(cmd->prev->pip[0], 0);
// 			dup2(cmd->pip[1], 1);
// 		}
// 	}
// }

// void	renewal_cmd(t_cmd *cmd)
// {
// 	char	**tmp;
// 	int		i;
// 	int		j;

// 	if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
// 	{
// 		i = 0;
// 		while (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
// 		{
// 			i += 2;
// 			i++;
// 		}
// 		j = -1;
// 		while (i > ++j)
// 			free(cmd->av[j]);
// 		if (!ft_calloc(cmd->ac - i, sizeof(char *), (void **)& tmp))
// 			return (0); //exit 처리
// 		j = 0;
// 		while (i < cmd->ac)
// 		{
// 			tmp[j] = cmd->av[i];
// 			i++;
// 			j++;
// 		}
// 	}
// }

// int	check_redirection(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->av[i])
// 	{
// 		if (cmd->av[i][0] == '>')
// 		{
// 			if (cmd->av[i][1] == '>') // >> 인 경우
// 			{
// 				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
// 				if (cmd->fd_out == -1)
// 					return (0); // error message 처리, errno에 상세내용이 저장됨
// 			}
// 			else // > 인 경우
// 				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		}
// 		if (cmd->av[i][0] == '<')
// 		{
// 			cmd->fd_in = open(cmd->av[i + 1], O_RDONLY);
// 			if (cmd->fd_in == -1)
// 				return (0); // error 처리
// 		}
// 		i++;
// 	}
// 	renewal_cmd(cmd);
// 	return (1);
// }

// void	execute_path(t_state *s, t_cmd *cmd)
// {

// }

// void	execute_cmd2(t_state *s, t_cmd *cmd)
// {
// 	if (!check_redirection(cmd)) // file 없거나 에러인 경우
// 	{
// 		// 에러처리?
// 	}
// 	else if (builtin(s, cmd)) // builtin 들어간경우
// 		return ;
// 	else if (!find_command(s, cmd)) // path 함수인경우
// 	{
// 		execute_path(s, cmd);
// 	}
// 	else // path에 함수가 없는 경우
// 	{
// 		if (s->input)
// 			printf("bash: %s: command not found\n", s->input); // av[0] 으로 수정해야함
// 		return ;
// 	}

// }

// void	execute(t_state *s, t_cmd *cmd)
// {
// 	t_cmd	*cur;
	
// 	if (!check_multiline_quote(cmd))
// 		write(1, "error : quote error\n", 21);
// 	else
// 	{
// 		cur = cmd;
// 		while (cur)
// 		{
// 			set_pipe(cmd);
// 			execute_cmd2(s, cur);
// 			//close_pipe
// 			cur = cur->next;
// 		}
// 	}
// }