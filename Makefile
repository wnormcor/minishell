# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/16 10:18:16 by wnormcor          #+#    #+#              #
#    Updated: 2021/02/01 22:14:52 by wnormcor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	minishell.c \
		env.c \
		tokenizer.c \
		tokcheck.c \
		parser.c \
		parser_vars.c \
		parser_check.c \
		executor.c \
		executor_execve.c \
		bi_cd_pwd_env_exit.c \
		bi_echo.c \
		bi_export.c \
		bi_export_change.c \
		bi_export_check.c \
		bi_unset.c \
		bi_unset_del.c \
		utils.c \
		signal.c

OBJS = $(addprefix obj/, $(SRCS:%.c=%.o))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc -Wall -Wextra -Werror $(OBJS) $(LIBFT) -o $(NAME)

obj/%.o : src/%.c src/minishell.h
	@mkdir -p obj
	gcc -Wall -Wextra -Werror -c -g $< -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJS)
	@if [ -d obj ]; then rmdir obj; fi

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
