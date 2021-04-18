/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 15:53:39 by llim             ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

# define ERROR_NULL -7
# define ERROR_RDIR -6
# define ERROR_COLON2 -5
# define ERROR_PIPE2 -4
# define ERROR_COLON -3
# define ERROR_PIPE -2
# define ERROR_QUOTE -1
# define COMMON 0
# define SPACE 1
# define SINGLE 2
# define DOUBLE 3
# define LEFT 4
# define RIGHT 5
# define DOUBLERIGHT 6
# define BACKSLASH 7
# define PIPE 8
# define SEMICOLON 9

# define ERROR 0

# define FALSE 0
# define TRUE 1

# define NORMAL_TYPE 0
# define PIPE_TYPE 8
# define COLON_TYPE 9

# define EXECVE_ERR 1
# define NOT_FOUND 2
# define IS_DIR 3
# define NO_F_OR_D 4

typedef struct		s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_term
{
	struct termios	term;
	struct termios	save;
	char			*cm;
	char			*ce;
}					t_term;

typedef struct		s_cmd
{
	char			**av;
	int				ac;
	int				type;
	int				pip[2];
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct		s_keypos
{
	int				col;
	int				row;
}					t_keypos;

typedef struct		s_save
{
	char			*input;
	int				flag;
	struct s_save	*prev;
	struct s_save	*next;
}					t_save;

typedef struct		s_state
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd_head;
	t_path			*path_head;
	t_term			t;
	t_save			*save_head;
	int				s_flag;
	char			*input;
	int				is_fork;
	int				ret;
	t_keypos		cur;
	t_keypos		max;
	t_keypos		start;
}					t_state;

t_state				g_state;

/*
**	main
*/
void				init_state(t_state *state);
void				prepare_token_and_cmd(t_state *state);

/*
**	free
*/
void				free_2d(char **array);

/*
**	signal
*/
void				handle_signal(int signo);

/*
**	prompt
*/
// void	prompt(t_state *state);
void				prompt2(t_state *state);
int					is_backslash(t_state *s);
void				handle_eof(t_state *s, char *input);

/*
**	execute
*/
void				execute(t_state *s, t_cmd *cmd, char **envp);
void				set_pipe(t_cmd *cmd);
// int		check_multiline_quote(t_cmd *cmd);
void				set_pipe(t_cmd *cmd);
char				**make_new_cmd(t_cmd *cmd, int cnt, char **new);
void				renewal_cmd(t_cmd *cmd);
int					check_redirection(t_cmd *cmd);
void				execute_error(t_state *s, t_cmd *cmd, int type);

/*
**	term
*/
void				init_term(t_state *s);
void				handle_keycode(t_state *s, int keycode);
int					term_loop(t_state *s);
void				put_backspace(t_state *s);

void				save_history(t_state *s);
t_save				*push_front_save(char *input, t_save *old_head, int flag);
void				reset_save(t_state *s);
void				press_up(t_state *s);
void				press_down(t_state *s);

/*
**	cursor
*/
int					get_nbr_len(int n);
void				set_cursor(int *col, int *row);
void				set_cursor_win(t_state *s);
/*
**	string_util
*/
int					ft_putchar(int c);
char				*ft_strcjoin(char *str, char c);
void				print_save_char(t_state *s, char c);
char				*delete_last_char(char *str);

/*
**	tokenizer
*/
void				tokenizer(t_state *state);
int					make_token(t_state *state, int count, int i, int type);
void				add_token_back(t_token **head, char *str, int type);
char				*trim_str(char *str, int type);
int					find_cur_type(t_token **head, int *has_space);
/*
**	token_check
*/
int					check_syntax_error(int cur_type,
											int next_type, int has_space);
int					check_deep_syntax_error(int cur_type,
											int next_type, int has_space);
void				check_token_error(t_state *state);
void				return_quote_error(t_state *state, t_token *token);
int					check_backslash_count(char *input, int i);

/*
**	token_util
*/
int					is_operator(char *c, int i);
int					get_len(char *input, int i);
int					find_end(t_state *state, int type, int i);
t_token				*create_token(char *str, int type);
void				free_token(t_token *token);

/*
**	env
*/
void				parse_env(char **envp, t_state *state);
void				add_env_back(t_env **head, char *key,
								char *value, int has_equal);
t_env				*create_env(char *key, char *value, int has_equal);
/*
**	env_util
*/
int					ft_strcmp(char *s1, char *s2);
void				print_env_all(t_env *head);
t_env				*find_env(t_env *head, char *key);
char				*find_env_val(t_env *head, char *key);
void				free_env(t_env *env);

/*
**	export
*/
void				print_export(t_env *env);
void				print_one_export(t_env *head, char *key);
void				update_env(t_env *head, char *key,
								char *value, int has_equal);
/*
**	export_util
*/
char				*make_env_string(char *key, char *value, int has_equal);
int					check_len(char *key, char *value, int has_equal);
int					check_env_length(t_env *env);
void				sorted_list(char **list, int size);

/*
**	GNL
*/
char				*ft_strjoin2(char *s1, char *s2);
int					get_next_line(int fd, char **line);

/*
**	builtin
*/
int					builtin(t_state *state, t_cmd *cmd);
int					ft_pwd(t_state *s, t_cmd *cmd);
void				ft_exit(t_state *state, t_cmd *cmd);
int					ft_cd(t_state *s, t_cmd *cmd);
void				ft_echo(t_state *t, t_cmd *cmd);
void				ft_unset(t_state *s, t_cmd *cmd);
void				ft_export(t_state *state, t_cmd *cmd, int i);

int					check_key(char *key);

/*
**	path
*/
void				parse_path(t_state *state);
void				add_path_back(t_path **head, char *path_str);
t_path				*create_path(char *path_str);
void				free_path(t_path *path);
void				make_path(t_cmd *cmd, char *str);

/*
**	cmd
*/
int					find_success_cmd(t_state *s, t_cmd *cmd,
									char *path, DIR *dir_ptr);
int					find_simple_cmd(t_cmd *cmd, int *err);
int					find_command(t_state *s, t_cmd *cmd);
void				execute_builtin(t_state *s, t_cmd *cmd);
void				set_fork_builtin(t_state *s, t_cmd *cmd);
int					builtin(t_state *s, t_cmd *cmd);
/*
**	cmd_parse
*/
void				parse_cmd(t_state *state, int ac);
void				make_cmd(t_state *state, t_token *start, int ac, int type);
char				*make_av(t_state *state, t_token *start, char *str);
void				add_cmd_back(t_cmd **head, char **av, int type);
t_cmd				*create_cmd(char **av, int ac, int type, t_cmd *prev);
/*
**	cmd_check
*/
void				check_backslash_and_env(t_state *state, t_token *start);
void				check_backslash(t_token *token);
void				check_dollar_sign(t_state *state, t_token *token);
char				*check_env(t_state *state, t_token *token,
								char *value, int *i);
char				*changed_str(char *origin, int start,
								int end, char *insert);

/*
**	cmd_util
*/
void				free_cmd(t_cmd *cmd);
void				check_env_space(t_state *state);
void				remove_space(t_token *token);
char				*removed_space(char *str);
int					check_key_len(char *str);

#endif
