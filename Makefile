.DEFAULT_GOAL = all

NAME=sVim
CC=cc
CFLAGS=-Wall -Wextra -Werror --std=c99 -MMD -MP -g3
SRCS= \
	 main.c \
	 skip_list.c \
	 screen.c \
	 user_interaction.c \

OBJS_DIR=.objs
OBJS=$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

DEPS_DIR=.deps
DEPS=$(addprefix $(DEPS_DIR)/, $(SRCS:.c=.d))
-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	$(LINK.c) $(OUTPUT_OPTION) $(OBJS)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR) $(DEPS_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

clean:
	rm -fr $(OBJS) $(DEPS)

fclean: clean
	rm -fr $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
