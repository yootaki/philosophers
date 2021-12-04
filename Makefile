
NAME	:= philo
COMPILER:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LIBS	:=
INCLUDE	:= -I./include
SRCS_DIR:= ./src
SRCS	:= main.c\
			thread.c\
			validate.c\
			init.c\
			philos_action.c\
			get_timestamp.c\
			get_forks.c\
			put_forks.c\
			ft_atoi.c\
			ft_isdigit.c
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
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

-include $(DEPS)
