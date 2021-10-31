
NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c ft_atoi.c test.c

OBJS = $(SRCS:.c=.o) $(UTILS:.c=.o)

DEBUG_DIR = philo.dSYM

# **************************************************
# **************************************************

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# **************************************************
# **************************************************

clean:
	$(RM) $(DEBUG_DIR) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************
# **************************************************

debug: CFLAGS += -g3 -fsanitize=address

debug: re

# **************************************************
# **************************************************

.PHONY: all debug fclean clean re
