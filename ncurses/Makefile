SHELL = /bin/sh

NAME = ../Lem_IPC_Ncurses
FLAGS = -Wall -Wextra -Werror -g3 -O0 -ggdb

SRCS = main.c printing.c
OBJS = $(SRCS:.c=.o)

HEADER_PATH = ./includes/
HEADERS = graphic.h

LIB_IPC_NAME = -lipc
LIB_IPC_PATH = ../
LIB_IPC_PATH_INCL = ../ipc_lib/includes

NCURSES_NAME = -lncurses
PTHREAD_NAME = -lpthread
RT_NAME = -lrt

vpath %.c ./sources
vpath %.h ./includes

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -o $(NAME) $(OBJS) -L$(LIB_IPC_PATH) $(LIB_IPC_NAME) $(NCURSES_NAME) $(PTHREAD_NAME) $(RT_NAME)

$(OBJS): %.o:%.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) -I$(LIB_IPC_PATH_INCL) $(FLAGS) -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
