# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 17:02:38 by llim              #+#    #+#              #
#    Updated: 2021/03/23 16:12:14 by dhyeon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
SRCS	=	srcs/main.c\
			srcs/signal.c \
			srcs/prompt.c \
			srcs/tokenizer.c \
			srcs/env.c\
			srcs/export.c\
			srcs/export_sort.c \
			srcs/get_next_line.c \
			srcs/ft_pwd.c \
			srcs/ft_exit.c \
			srcs/ft_cd.c \
			srcs/ft_echo.c \
			srcs/ft_unset.c

INCS	=	-I includes -I libft
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
LFT		=	-L libft -lft

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
