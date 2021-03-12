/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 06:56:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/13 01:38:35 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

int				get_next_line(int fd, char **line);
int				get_index(char *back);
int				gnl_return(char **back, char **line, char *buf);
char			*ft_strjoin2(char *s1, char *s2);

#endif
