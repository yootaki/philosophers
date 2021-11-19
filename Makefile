
NAME	:= philo
COMPILER:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LIBS	:=
INCLUDE	:= -I./include
SRCS_DIR:= ./src
SRCS	:= main.c init.c get_forks.c put_forks.c ft_atoi.c is_digit.c
OBJS_DIR:= ./obj
OBJS	:= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS	:= $(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBS)
	$(COMPILER) -o $@ $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(NAME)

clean:
	rm -f $(NAME) $(OBJS) $(DEPS)

fclean: clean

re: fclean all

debug: CFLAGS += -fsanitize=thread -g -O1

debug: re

.PHONY: all clean fclean re debug

-include $(DEPS)
