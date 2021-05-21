#ifndef LEM_IPC_H
# define LEM_IPC_H

# define TEAM_COUNT 4
# define MAP_X 20
# define MAP_Y 20
# define SHM_MAP_NAME "game_map"


# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

void check_input(int ac, char **av);
void create_shm(void);

#endif
