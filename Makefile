CC = cc
CFLAG = -Wall -Werror -Wextra

M_DIR = philo
M_SRC = $(patsubst %, M_DIR/%, main.c)
M_HDRS = $(patsubst %, M_DIR/%, main.h)
M_OBJ = $(patsubst %.c, %.o, $(M_SRC))

NAME = philosophers

M_TARGET = philo

all: $(NAME)

$(NAME): $(M_TARGET)

$(M_TARGET): $(M_OBJ)
	$(CC) $(CFLAG) $^ -o $@


re: fclean all

clean:
	rm -rf $(M_OBJ)

flcean: clean
	rm -rf $(M_TARGET)

.PHONY: re all clean fclean $(NAME)
