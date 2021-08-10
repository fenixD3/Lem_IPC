SHELL = /bin/sh

LEM_IPC_PATH = ./sources
IPC_LIB_PATH = ./ipc_lib
LEM_IPC_NCURSES_PATH = ./ncurses

.PHONY: all clean fclean re
all:
	$(MAKE) -C $(IPC_LIB_PATH)
	$(MAKE) -C $(LEM_IPC_PATH)
	$(MAKE) -C $(LEM_IPC_NCURSES_PATH)

clean:
	$(MAKE) -C $(IPC_LIB_PATH) clean
	$(MAKE) -C $(LEM_IPC_PATH) clean
	$(MAKE) -C $(LEM_IPC_NCURSES_PATH) clean

fclean:
	$(MAKE) -C $(IPC_LIB_PATH) fclean
	$(MAKE) -C $(LEM_IPC_PATH) fclean
	$(MAKE) -C $(LEM_IPC_NCURSES_PATH) fclean

re:
	$(MAKE) -C $(IPC_LIB_PATH) re
	$(MAKE) -C $(LEM_IPC_PATH) re
	$(MAKE) -C $(LEM_IPC_NCURSES_PATH) re