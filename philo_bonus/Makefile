# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 17:48:41 by zmoumen           #+#    #+#              #
#    Updated: 2023/03/05 17:58:36 by zmoumen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wall -Werror -Wextra

M_SRC = main_bonus.c tools_bonus.c cleanup_bonus.c philo_runtime_bonus.c runtime_monitors_bonus.c
M_HDRS = philo_bonus.h
M_OBJ = $(patsubst %.c, %.o, $(M_SRC))

NAME = philosophers

M_TARGET = philo_bonus

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAG) $^ -c -o $@

$(NAME): $(M_TARGET)

$(M_TARGET): $(M_OBJ)
	$(CC) $(CFLAG) $^ -o $@

bonus:all clean

re: fclean all

clean:
	rm -rf $(M_OBJ)

fclean: clean
	rm -f $(M_TARGET)

.PHONY: re all clean fclean $(NAME) bonus
