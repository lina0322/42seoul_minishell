/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 23:51:20 by llim             ###   ########.fr       */
=======
/*   Updated: 2021/04/07 21:47:24 by dhyeon           ###   ########.fr       */
>>>>>>> 97fe65df26931e7a805a04451832fb594109e50b
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <dirent.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

# define COMMON 0
# define SPACE 1
# define SINGLE 2
# define DOUBLE 3
# define LEFT 4
# define RIGHT 5
# define DOUBLERIGHT 6
# define SEMICOLON 7
# define PIPE 8
# define BACKSLASH 9

# define ERROR 0

# define FALSE 0
# define TRUE 1

# define NORMAL_TYPE 0
# define COLON_TYPE 1
# define PIPE_TYPE 2

typedef struct s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct s_term
{
	struct termios	term;
	char			*cm;
	char			*ce;
}					t_term;

typedef struct s_cmd
{
	char			**av;
	int				ac;
	int				type;
	int				pip[2];
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_keypos
{
	int				col;
	int				row;
}					t_keypos;

typedef struct s_state
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd_head;
	t_path			*path_head;
	t_term			t;
	char			*input;
	int				ret;
	t_keypos		cur;
	t_keypos		max;
	t_keypos		start;
}					t_state;

/*
**	main
*/
void	init_state(t_state *state);
void	prepare_token_and_cmd(t_state *state);
void	free_2d(char **array);

/*
**	signal
*/
void	handle_signal(int signo);

/*
**	prompt
*/
void	prompt(t_state *state);
void	prompt2(t_state *state);
int		ft_putchar(int c);
void	set_cursor(int *col, int *row);
char	*delete_last_char(char *str);

/*
**	tokenizer
*/
void	tokenizer(t_state *state);
int		make_token(t_state *state, int count, int i, int type);
void	add_token_back(t_token **head, char *str, int type);
t_token	*create_token(char *str, int type);
/*
**	token_util
*/
int		is_operator(char *c, int i);
int		get_len(char *input, int i);
int		find_end(char *input, int type, int i);
void	free_token(t_token *token);

/*
**	env
*/
void	parse_env(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value, int has_equal);
t_env	*create_env(char *key, char *value, int has_equal);
t_env	*find_env(t_env *head, char *key);
void	print_env_all(t_env *head);
char	*find_env_val(t_env *head, char *key);
int		ft_strcmp(char *s1, char *s2);
void	free_env(t_env *env);

/*
**	export
*/
void	print_export(t_env *env);
void	print_one_export(t_env *head, char *key);
void	update_env(t_env *head, char *key, char *value, int has_equal);
/*
**	export_util
*/
char	*make_env_string(char *key, char *value, int has_equal);
int		check_env_length(t_env *env);
void	sorted_list(char **list, int size);

/*
**	GNL
*/
char	*ft_strjoin2(char *s1, char *s2);
int		get_next_line(int fd, char **line);

/*
**	builtin
*/
int		builtin(t_state *state, t_cmd *cmd);
int		ft_pwd(t_state *s, t_cmd *cmd);
int		ft_pwd(t_state *state, t_cmd *cmd);
int		ft_exit(t_state *state, t_cmd *cmd);
int		ft_cd(t_state *s, t_cmd *cmd);
void	ft_echo(t_state *t, t_cmd *cmd);
void	ft_unset(t_state *s, t_cmd *cmd);
void	ft_export(t_state *state, t_cmd *cmd);

int		check_key(char *key);
int		find_command(t_state *s, t_cmd *cmd);

/*
**	path
*/
void	parse_path(t_state *state);
void	add_path_back(t_path **head, char *path_str);
t_path	*create_path(char *path_str);
void	free_path(t_path *path);

/*
**	cmd
*/
void	make_path(t_cmd *cmd, char *str);
int		find_command(t_state *s, t_cmd *cmd);
int		builtin(t_state *s, t_cmd *cmd);
/*
**	cmd_parse
*/
void	parse_cmd(t_state *state);
void	make_cmd(t_state *state, t_token *start, int ac, int type);
void	check_env(t_state *state, t_token *token);
void	check_backslash(t_token *token);
void	add_cmd_back(t_cmd **head, char **av, int type);
t_cmd	*create_cmd(char **av, int ac, int type);
void	free_cmd(t_cmd *cmd);

#endif
