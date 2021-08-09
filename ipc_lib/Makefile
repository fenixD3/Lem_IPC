SHELL = /bin/sh

NAME = ../libipc.so
FLAGS = -Wall -Wextra -Werror -fPIC -g3 -O0 -ggdb
SHARED_FLAG = -shared

SRCS = ipc_creation.c ipc_freeing.c utils.c
OBJS = $(SRCS:.c=.o)

HEADER_PATH = ./includes/
HEADERS = ipc_lib.h

vpath %.c ./sources
vpath %.h ./includes

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(SHARED_FLAG) -o $(NAME) $(OBJS)

$(OBJS): %.o:%.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) $(FLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all