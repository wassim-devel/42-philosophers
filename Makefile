CC=cc
CFLAGS=-Wall -Wextra -Werror
HEADER=./philo.h
NAME=philo
SRCS= ./frees.c ./init_and_threading.c ./init_util.c ./philo.c ./philo_eat_funcs.c ./utils.c ./thread_utils.c ./thread_utils2.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ #-O3

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re