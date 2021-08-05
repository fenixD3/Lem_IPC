#include "graphic.h"
#include <stdlib.h>

t_graphic *init_ncurse(void)
{
	t_graphic *ncurse;

	if (!(ncurse = malloc(sizeof(t_graphic))))
	{
		perror("create_ncurse");
		exit(EXIT_FAILURE);
	}

	if (!(ncurse->ipcs = malloc(sizeof(t_ipcs))))
	{
		perror("create_ipcs");
		exit(EXIT_FAILURE);
	}

	ncurse->ipcs->shm_addr = get_shm(SHM_MAP_NAME, MAP_SIZE, 0);
	ncurse->ipcs->sem = get_sem(SEM_NAME, 0, SEM_DEFAULT_VALUE);
	ncurse->pid = getpid();

	initscr();
	noecho();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	return ncurse;
}

void delete_ncurse(t_graphic **ncurse)
{
	close_sem(&(*ncurse)->ipcs->sem);
	free((*ncurse)->ipcs);
	free(ncurse);
	endwin();
}

int main(int ac, char **av)
{
	t_graphic *ncurse = init_ncurse();
	loop(ncurse);
	delete_ncurse(&ncurse);
	return 0;
}
