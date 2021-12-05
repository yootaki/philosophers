
NAME	:= philo
COMPILER:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LIBS	:=
INCLUDE	:= -I./include
SRCS_DIR:= ./src
SRCS	:= main.c\
			check_status.c\
			thread.c\
			validate.c\
			init.c\
			philos_action.c\
			get_timestamp.c\
			get_forks.c\
			put_forks.c\
			free_all.c\
			atoi.c\
			is_correct_value.c
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
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

-include $(DEPS)
