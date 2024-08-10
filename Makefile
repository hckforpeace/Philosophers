SRC= main.c display.c mutex.c routines.c threads.c time.c parser.c data.c
OBJ= $(addprefix src/,$(SRC:.c=.o))
NAME= philo
CC= cc
CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $^ -lft -L./libft -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I./Include -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft