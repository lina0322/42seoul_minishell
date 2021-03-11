/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/11 17:36:01 by dhyeon           ###   ########.fr       */
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


#endif
