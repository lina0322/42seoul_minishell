/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 00:11:04 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
 *	parse_env
 */

void	parse_env(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value);
t_env	*create_env(char *key, char *value);

/*
 * util <- for test
 */

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
int		ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
