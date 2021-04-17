# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 17:02:38 by llim              #+#    #+#              #
#    Updated: 2021/04/17 20:22:01 by dhyeon           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address -arch x86_64
SRCS	=	srcs/main.c\
			srcs/signal.c \
			srcs/prompt.c \
			srcs/tokenizer.c \
			srcs/token_util.c \
			srcs/env.c\
			srcs/env_util.c\
			srcs/export.c\
			srcs/export_util.c \
			srcs/get_next_line.c \
			srcs/ft_pwd.c \
			srcs/ft_exit.c \
			srcs/ft_cd.c \
			srcs/ft_echo.c \
			srcs/ft_unset.c \
			srcs/ft_export.c \
			srcs/cmd.c \
			srcs/cmd_parse.c \
			srcs/cmd_check.c \
			srcs/path.c \
			srcs/execve.c \
			srcs/execve_util.c \
			srcs/string_util.c \
			srcs/term.c \
			srcs/cursor.c \
			srcs/history.c \
			srcs/press_arrow.c \
			srcs/free.c

INCS	=	-I includes -I libft
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
LFT		=	-L libft -lft -lncurses

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT) $(INCS)

$(LIBFT) :
	@make -C libft/

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	@make clean -C libft/
	rm -rf $(OBJS)

fclean : clean
	@make fclean -C libft/
	rm -rf $(NAME)

re : fclean all
