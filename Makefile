SRC= main.c
OBJ= $(addprefix src/,$(SRC:.c=.o))
NAME= philo
CC= cc
CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -lft -L./libft -o $@

%.o: %.c
	make -C libft
	$(CC) $(CFLAGS) -I./Include -c $< -o $@ 