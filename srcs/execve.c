/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:32 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/14 16:49:56 by dhyeon           ###   ########.fr       */
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

int	check_multiline_quote(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == -1)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	set_pipe(t_cmd *cmd)
{
	if (cmd->type == PIPE_TYPE ||
		(cmd->next != 0 && cmd->next->type == PIPE_TYPE))
	{
		if (cmd->type != PIPE_TYPE)
			dup2(cmd->pip[1], 1);
		else if (cmd->next == 0 || cmd->type == COLON_TYPE)
			dup2(cmd->prev->pip[0], 0);
		else
		{
			dup2(cmd->prev->pip[0], 0);
			dup2(cmd->pip[1], 1);
		}
	}
}

void	renewal_cmd(t_cmd *cmd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = 0;
	if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
	{
		while (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
		{
			i += 2;
			i++;
		}
		i--;
		j = -1;
		while (i > ++j)
			free(cmd->av[j]);
		if (!ft_calloc(cmd->ac - i + 1, sizeof(char *), (void **)& tmp))
			return ; //exit 처리
		j = 0;
		while (i < cmd->ac)
		{
			tmp[j] = cmd->av[i];
			i++;
			j++;
		}
		free(cmd->av);
		cmd->av = tmp;
		cmd->ac = j;
		tmp[j] = 0;
		printf("redirection : %s\n", cmd->av[0]); //test
	}
}

int	check_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	while (cmd->av[i])
	{
		if (cmd->av[i][0] == '>')
		{
			if (cmd->av[i][1] == '>') // >> 인 경우
			{
				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (cmd->fd_out == -1)
					return (0); // error message 처리, errno에 상세내용이 저장됨
			}
			else // > 인 경우
				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		if (cmd->av[i][0] == '<')
		{
			cmd->fd_in = open(cmd->av[i + 1], O_RDONLY);
			if (cmd->fd_in == -1)
				return (0); // error 처리
		}
		i++;
	}
	renewal_cmd(cmd);
	return (1);
}

void	execute_error(t_cmd *cmd, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(cmd->av[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (errno == 13)
			exit(126);
		else if (errno == 2)
			exit(127);
		exit(1);
	}
	else if (type == 2)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(cmd->av[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found\n", 2);
	}
}

void	execute_path(t_state *s, t_cmd *cmd, char **envp)
{
	int		status;
	pid_t	pid;
	(void)s;
	(void)cmd;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		set_pipe(cmd);
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, 0);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, 1);
		if (execve(cmd->av[0], cmd->av, envp) < 0)
			execute_error(cmd, 1);
	}
	else
	{
		close(cmd->pip[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			s->ret = WEXITSTATUS(status);
	}
}

void	execute_cmd2(t_state *s, t_cmd *cmd, char **envp)
{
	if (!check_redirection(cmd)) // file 없거나 에러인 경우
	{
		// 에러처리?
	}
	else if (builtin(s, cmd)) // builtin 들어간경우
		return ;
	else if (find_command(s, cmd) ||
		(cmd->av[0][0] == '/' && find_simple_cmd(cmd)) ) // path 함수인경우
	{
		execute_path(s, cmd, envp);
	}
	else // path에 함수가 없는 경우
	{
		execute_error(cmd, 2); // av[0] 으로 수정해야함
		return ;
	}

}

void	close_fd_dup(t_cmd *cmd, int *stin, int *stout)
{
	if (cmd->prev != 0)
		close(cmd->prev->pip[0]);
	close(cmd->pip[1]);
	if (cmd->next == 0)
		close(cmd->pip[0]);

	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	dup2(*stin, 0);
	dup2(*stout, 1);
	close(*stin);
	close(*stout);
}

void	execute(t_state *s, t_cmd *cmd, char **envp)
{
	t_cmd	*cur;
	int		stin;
	int		stout;

	if (!check_multiline_quote(cmd))
		write(1, "error : quote error\n", 21);
	else
	{
		cur = cmd;
		while (cur)
		{
			pipe(cur->pip);
			// set_pipe(cmd);
			stin = dup(0);
			stout = dup(1);
			execute_cmd2(s, cur, envp);
			close_fd_dup(cur, &stin, &stout);

			//close_pipe
			cur = cur->next;
		}
	}
}
