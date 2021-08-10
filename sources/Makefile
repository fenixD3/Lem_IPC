SHELL = /bin/sh

NAME = ../Lem_IPC
FLAGS = -Wall -Wextra -Werror -g3 -O0 -ggdb

SRCS = check_input.c directions.c enemy_searching.c game.c graphic.c ipc_management.c main.c moving.c \
	player_management.c signals.c logger.c logger_utils.c
OBJS = $(SRCS:.c=.o)

HEADER_PATH = ../includes/
HEADER_LOGGER_PATH = ../includes/logger
HEADERS = lem_ipc.h logger.h

LIB_IPC_NAME = -lipc
LIB_IPC_PATH = ../
LIB_IPC_PATH_INCL = ../ipc_lib/includes

PTHREAD_NAME = -lpthread
RT_NAME = -lrt

vpath %.c ./logger
vpath %.h ../includes ../includes/logger

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -o $(NAME) $(OBJS) -L$(LIB_IPC_PATH) $(LIB_IPC_NAME) $(PTHREAD_NAME) $(RT_NAME)

$(OBJS): %.o:%.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) -I$(HEADER_LOGGER_PATH) -I$(LIB_IPC_PATH_INCL) $(FLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
