#ifndef GRAPHIC_H
#define GRAPHIC_H

#define TEAM_COUNT 4
#define TEAM_NUM_CNT 1
#define MAP_X 20
#define MAP_SIZE MAP_X * MAP_X

#define MAP_FILLER '.'

#define SHM_MAP_NAME "game_map"
#define SEM_NAME "/game_sem"
#define SEM_DEFAULT_VALUE 1

#include <ncurses.h>
#include "ipc_lib.h"

typedef struct s_graphic
{
	pid_t pid;
	t_ipcs *ipcs;
} t_graphic;

t_graphic *init_ncurse(void);
void delete_ncurse(t_graphic **ncurse);
void loop(t_graphic *ncurse);

bool is_finished(const int *team_cnt);

void print_line(t_graphic *ncurse, int y, int *team_cnt, bool *is_living_team);
void print_row(int y);

#endif
