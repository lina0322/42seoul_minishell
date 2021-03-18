/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/18 19:53:16 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			**av;
	int				ac;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_state
{
	t_token		*token_head;
	t_env		*env_head;
	t_cmd		*cmd;
	char		*input;
}				t_state;

/*
 * main
 */

void	init_state(t_state *state);

/*
 * signal
 */

void	handle_signal(int signo);

/*
 *	prompt
 */

void	prompt(t_state *state);

/*
 *	env
 */

void	parse_env(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value);
t_env	*create_env(char *key, char *value);
t_env	*find_env(t_env *head, char *key);
void	print_env_all(t_env *head);
char	*find_env_val(t_env *head, char *key);

/*
 *	sorted_export
 */

char	*make_env_string(char *key, char *value);
int		check_env_length(t_env *env);
void	sorted_list(char **list, int size);

/*
 * export
 */

void	print_export(t_env *env);
void	print_one_export(t_env *head, char *key);
void	update_env(t_env *head, char *key, char *value);

char	*ft_strjoin2(char *s1, char *s2);
int		get_next_line(int fd, char **line);

int		builtin(t_state *state, t_cmd *cmd);
int		ft_pwd(t_state *state, t_cmd *cmd);
int		ft_exit(t_state *state, t_cmd *cmd);
int		ft_cd(t_state *s, t_cmd *cmd);



#endif
