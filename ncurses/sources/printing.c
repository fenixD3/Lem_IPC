#include "graphic.h"

void loop(t_graphic *ncurse)
{
	int y;

	while(true)
	{
		sem_wait(ncurse->ipcs->sem);
		y = 0;
		while (y < MAP_X)
		{
			print_line(ncurse, y);
			y++;
		}
		print_row(y * 2);
		sem_post(ncurse->ipcs->sem);
		refresh();
		sleep(1);
	}
}

void print_row(int y)
{
	int						x;

	x = 0;
	while (x < MAP_X * 3)
	{
		mvprintw(y, x++, "+");
		mvprintw(y, x++, "-");
		mvprintw(y, x++, "-");
	}
	mvprintw(y, x++, "+");
}

void print_line(t_graphic *ncurse, int y)
{
	int						j;
	int						x;
	int						team;

	j = y * 2;
	print_row(j++);
	x = 0;
	while (x < MAP_X * 3)
	{
		if (!check_out_of_map_bound(x, j, MAP_X) && check_occupied_cell(ncurse->ipcs->shm_addr, x, j, MAP_X))
			team = get_number_from_map(ncurse->ipcs->shm_addr, x, j, TEAM_NUM_CNT, MAP_X);
		else
			team = 0;
		mvprintw(j, x++, "|");
		attron(COLOR_PAIR(team));
		mvprintw(j, x++, " ");
		if (team != 0)
			mvprintw(j, x, "%d", team);
		else
			mvprintw(j, x, "%c", MAP_FILLER);
		x++;
		attron(COLOR_PAIR(8));
	}
	mvprintw(j, x, "|");
}
