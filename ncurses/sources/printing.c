#include "graphic.h"

void loop(t_graphic *ncurse)
{
	int y;

	while(true)
	{
		int team_cnt[TEAM_COUNT] = {0};
		sem_wait(ncurse->ipcs->sem);
		y = 0;
		while (y < MAP_X)
		{
			print_line(ncurse, y, team_cnt);
			y++;
		}
		print_row(y * 2);
		mvprintw(y * 2 + 1, 0, "%d", getppid());
		mvprintw(y * 2 + 2, 0, "%d", getpid());
		sem_post(ncurse->ipcs->sem);
		refresh();
		if (is_finished(team_cnt))
			return;
		sleep(1);
	}
}

void print_row(int y)
{
	int x;

	x = 0;
	while (x < MAP_X * 3)
	{
		mvprintw(y, x++, "+");
		mvprintw(y, x++, "-");
		mvprintw(y, x++, "-");
	}
	mvprintw(y, x++, "+");
}

void print_line(t_graphic *ncurse, int y, int *team_cnt)
{
	int	j, x, team;

	j = y * 2;
	print_row(j++);
	x = 0;
	while (x < MAP_X * 3)
	{
		if (!check_out_of_map_bound(j / 2, x / 3, MAP_X) && check_occupied_cell(ncurse->ipcs->shm_addr, j / 2, x / 3, MAP_X))
		{
			team = get_number_from_map(ncurse->ipcs->shm_addr, j / 2, x / 3, TEAM_NUM_CNT, MAP_X);
			team_cnt[team - 1] += 1;
		}
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
		attron(COLOR_PAIR(5));
	}
	mvprintw(j, x, "|");
}

bool is_finished(const int *team_cnt)
{
	bool is_prev_team = false;

	for (int team = 0; team < TEAM_COUNT; ++team)
	{
		if (team_cnt[team] != 0 && is_prev_team)
			return false;
		else if (team_cnt[team] != 0)
			is_prev_team = true;
	}
	return is_prev_team;
}
