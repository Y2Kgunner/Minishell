# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 12:19:45 by lel-khou          #+#    #+#              #
#    Updated: 2022/11/02 23:48:08 by ykulkarn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -lreadline

HEADER = minishell.h

LIBFT = libft.a

LIBS = -L./libft -lft

NAME = minishell

LDFLAGS = -lreadline -L /usr/local/Cellar/readline/8.1/lib/

RM = rm -f

SRC = main.c split.c parser.c expander.c utils.c env_list.c env_split.c utils_split.c \
	remove_space.c export.c utils_free.c utils_export.c split_pipes_redirections.c \
	pipes.c redirections.c chdir.c utils_pipes.c signals.c shlvl.c convert_list.c \
	free.c path.c externals.c

OBJS = $(SRC:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

clean :
	$(RM) $(OBJS)
	@make clean -C libft

fclean : clean
	$(RM) $(NAME)
	@make fclean -C libft

re : fclean all
