NAME = philo

HDRS = philo.h

SRCS =	init.c \
		philo.c \
		valid.c \
		work.c \
		start.c \
		utils.c \

OBJS = 	$(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -I $(HDRS) -o $@

%.o: %.c $(HDRS)
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus