#include "../includes/graphic.h"
#include <stdlib.h>

t_graphic *init_ncurse(void)
{
	t_graphic *ncurse;

	if (!(ncurse = malloc(sizeof(t_graphic))))
	{
		perror("init_ncurse");
		exit(EXIT_FAILURE);
	}

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
}

int main(int ac, char **av)
{
	return 0;
}

