# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyeon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/01 23:08:08 by dhyeon            #+#    #+#              #
#    Updated: 2020/07/06 17:50:06 by dhyeon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putstr_fd \
		ft_putnbr_fd

B_FILES =	ft_lstnew \
			ft_lstadd_front \
			ft_lstsize \
			ft_lstlast \
			ft_lstadd_back \
			ft_lstdelone \
			ft_lstclear \
			ft_lstiter \
			ft_lstmap

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
B_SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(B_FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
B_OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(B_FILES)))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: bonus all clean fclean re

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus: $(B_OBJS) $(OBJS)
	ar rcs $(NAME) $^

all: $(NAME)

clean:
	rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all
