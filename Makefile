.DEFAULT_GOAL = all

NAME=sVim
CC=cc
CFLAGS=-Wall -Wextra -Werror --std=c99 -MMD -MP -g3
SRCS= \
	 main.c \
	 skip_list.c \

OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	$(LINK.c) $(OUTPUT_OPTION) $(OBJS)

%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm -fr $(OBJS) $(DEPS)

fclean: clean
	rm -fr $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
