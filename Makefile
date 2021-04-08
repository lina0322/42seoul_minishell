# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 17:02:38 by llim              #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/04/08 23:41:28 by llim             ###   ########.fr        #
=======
#    Updated: 2021/04/08 05:34:54 by dhyeon           ###   ########.fr        #
>>>>>>> f2dd6ff65a6ea4e4c1f548059cabec90a52cfccc
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -arch x86_64 # -fsanitize=address
SRCS	=	srcs/main.c\
			srcs/signal.c \
			srcs/prompt.c \
			srcs/tokenizer.c \
			srcs/token_util.c \
			srcs/env.c\
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
			srcs/path.c \
			srcs/execve.c \
			srcs/string_util.c \
			srcs/term.c \
			srcs/cursor.c

INCS	=	-I includes -I libft
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
LFT		=	-L libft -lft -lcurses

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
