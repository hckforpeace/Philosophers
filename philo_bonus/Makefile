SRC= main.c init.c parser.c children.c utils.c libft_utils.c display.c
OBJ= $(addprefix src/,$(SRC:.c=.o))
NAME= philo_bonus
CC= cc
CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -pthread

%.o: %.c
	$(CC) $(CFLAGS) -I./Include -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all