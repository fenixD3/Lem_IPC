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
	if (has_colors() && COLOR_PAIRS >= TEAM_COUNT + 1)
	{
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_WHITE, COLOR_BLACK);
	}

	return ncurse;
}

void delete_ncurse(t_graphic **ncurse)
{
	close_sem(&(*ncurse)->ipcs->sem);
	free((*ncurse)->ipcs);
	free(*ncurse);
	endwin();
}

int main(void)
{
	t_graphic *ncurse = init_ncurse();
	sleep(1);
	loop(ncurse);
	delete_ncurse(&ncurse);
	return 0;
}
