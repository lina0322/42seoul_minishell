/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/12 23:40:14 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char		*key;
	char		*value;
	t_env		*next;
}				t_env;

typedef struct s_token
{
	char		*str;
	int			type;
	t_token		*next;
}				t_token;

typedef struct s_state
{
	t_token		*token_head;
	t_env		*env_head;
	char		*input;
}				t_state;

/*
 *	parse_env
 */

void	parse_evn(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value);
t_evn	*create_env(char *key, char *value);

#endif
