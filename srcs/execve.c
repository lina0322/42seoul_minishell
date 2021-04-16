/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:32 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/17 05:03:36 by dhyeon           ###   ########seoul.kr  */
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

char	**make_new_cmd(t_cmd *cmd, int cnt, char **new)
{
	int	i;
	int	j;

	if (!ft_calloc(cnt + 1, sizeof(char *), (void **)& new))
		return (0); //exit 처리
	i = 0;
	j = 0;
	while (cmd->ac > i)
	{
		if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
			i++;
		else
		{
			new[j] = ft_strdup(cmd->av[i]);
			if (!new[j])
				return (0); //exit처리
			j++;
		}
		i++;
	}
	new[cnt] = 0;
	return (new);
}

void	renewal_cmd(t_cmd *cmd)
{
	char	**new;
	int		cnt;
	int		i;

	i = 0;
	cnt = 0;
	while (cmd->ac > i)
	{
		if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
			cnt++;
		i++;
	}
	if (cnt == 0)
		return ;
	cnt = cmd->ac - (cnt * 2);
	new = 0;
	new = make_new_cmd(cmd, cnt, new);
	free_2d(cmd->av);
	cmd->av = new;
	cmd->ac = cnt;
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

void	execute_error(t_state *s, t_cmd *cmd, int type)
{
	if (type == EXECVE_ERR)
	{
		printf("bash: %s: %s\n", cmd->av[0], strerror(errno));
		if (errno == 13)
			exit(126);
		else if (errno == 2)
			exit(127);
		exit(1);
	}
	else if (type == NOT_FOUND || type == NO_F_OR_D)
	{
		if (type == 2)
			printf("bash: %s: command not found\n", cmd->av[0]);
		else if (type == 4)
			printf("bash: %s: No such file or directory\n", cmd->av[0]);
		s->ret = 127;
	}
	else if (type == IS_DIR)
	{
		printf("bash: %s: is a directory\n", cmd->av[0]);
		s->ret = 126;
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
			execute_error(s, cmd, 1);
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
	int	err;

	if (!check_redirection(cmd)) // file 없거나 에러인 경우
	{
		printf("bash: %s: %s\n", cmd->av[2], strerror(errno));
	}
	else if (builtin(s, cmd)) // builtin 들어간경우
		return ;
	else if (find_command(s, cmd)) // path 함수인경우
		execute_path(s, cmd, envp);
	else if (cmd->av[0][0] == '/')
	{
		// ret = find_simple_cmd(cmd);
		if (find_simple_cmd(cmd, &err))// path함수인 경우
			execute_path(s, cmd, envp);
		else
			execute_error(s, cmd, err);
	}
	else // path에 함수가 없는 경우
		execute_error(s, cmd, 2); // av[0] 으로 수정해야함
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

void	handle_syntax_error(t_state *s, t_cmd *cmd)
{
	if (cmd->type == ERROR_PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (cmd->type == ERROR_COLON)
		printf("bash: syntax error near unexpected token `;'\n");
	else if (cmd->type == ERROR_PIPE2)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (cmd->type == ERROR_COLON2)
		printf("bash: syntax error near unexpected token `;;'\n");
	s->ret = 258;
}

void	execute(t_state *s, t_cmd *cmd, char **envp)
{
	t_cmd	*cur;
	int		stin;
	int		stout;

	//syntax error check
	if (!check_multiline_quote(cmd))
		write(1, "error : quote error\n", 21);
	else if (cmd->type < 0)
		handle_syntax_error(s, cmd);
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
	save_history(s);
}
