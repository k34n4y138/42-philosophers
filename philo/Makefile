CC = cc
CFLAG = -Wall -Werror -Wextra

M_SRC = main.c events_helpers.c philo_runtime.c runtime_monitor.c spinup_routines.c tools.c
M_HDRS = philo.h
M_OBJ = $(patsubst %.c, %.o, $(M_SRC))

NAME = philosophers

M_TARGET = philo

all: $(NAME)

%.o:%.c $(M_HDRS)
	$(CC) $(CFLAG) $^ -c -o $@

$(NAME): $(M_TARGET)

$(M_TARGET): $(M_OBJ)
	$(CC) $(CFLAG) $^ -o $@


re: fclean all

clean:
	rm -rf $(M_OBJ)

fclean: clean
	rm -f $(M_TARGET)

.PHONY: re all clean fclean $(NAME)
