/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 16:18:22 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

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

typedef struct s_state
{
	t_token		*token_head;
	t_env		*env_head;
	char		*input;
}				t_state;

void	init_state(t_state *state);

/*
 *	env
 */

void	parse_env(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value);
t_env	*create_env(char *key, char *value);
void	print_env_all(t_env *head);

/*
 *	prompt
 */

void	prompt(t_state *state);

/*
 *	export
 */

void	print_export_sorted_list(t_env *env);
char	*make_export_env(char *key, char *value);
int		check_env_length(t_env *env);
void	sorted_list(char **list, int size);
#endif
