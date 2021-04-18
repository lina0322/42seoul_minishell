/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 04:34:29 by dhyeon            #+#    #+#             */
/*   Updated: 2021/04/18 19:18:24 by dhyeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	int		i;

	if (!(s1) && !(s2))
		return (0);
	else if (!(s1) || !(s2))
	{
		if (!(s1))
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	if (!ft_calloc(sizeof(char), len + 1, (void *)& res))
		exit(1);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

int		get_index(char *back)
{
	int	i;

	i = 0;
	if (back == 0)
		return (-1);
	while (back[i])
	{
		if (back[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		gnl_return(char **back, char **line, char *buf)
{
	char	*back_tmp;
	int		idx;

	if (buf != 0)
		free(buf);
	idx = get_index(*back);
	if (idx != -1)
	{
		back_tmp = ft_strdup(*back);
		free(*back);
		back_tmp[idx] = '\0';
		*line = ft_strdup(back_tmp);
		*back = ft_strdup(back_tmp + idx + 1);
		if (back_tmp != 0)
			free(back_tmp);
		return (GNL_SUCCESS);
	}
	if (*back != 0)
	{
		*line = *back;
		*back = 0;
	}
	else
		*line = ft_strdup("");
	return (GNL_EOF);
}

int		get_next_line(int fd, char **line)
{
	static char	*back[FOPEN_MAX];
	char		*buf;
	char		*tmp;
	int			gnl_read;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (GNL_ERROR);
	if (!ft_calloc(sizeof(char), BUFFER_SIZE + 1, (void *)& buf))
		exit(1);
	while ((get_index(back[fd]) == -1)
		&& ((gnl_read = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[gnl_read] = '\0';
		tmp = back[fd];
		back[fd] = ft_strjoin2(back[fd], buf);
		if (tmp != 0)
			free(tmp);
	}
	if (gnl_read < 0)
	{
		free(buf);
		return (GNL_ERROR);
	}
	return (gnl_return(&back[fd], line, buf));
}
