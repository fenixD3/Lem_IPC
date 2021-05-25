#include "lem-ipc.h"
#include <time.h>

#define BEGIN_RAND_DIAPASON 0
#define END_RAND_DIAPASON MAP_X

void	fill_player_info(t_player *player, t_ipcs *ipcs, int team_number)
{
	player->team_number = team_number;
	player->ipcs = ipcs;
}

void	find_starting_place(t_player *player)
{
	int position_x;
	int position_y;

	srand(time(NULL));
	position_x = BEGIN_RAND_DIAPASON +
		(int)(END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	position_y = BEGIN_RAND_DIAPASON +
		(int)(END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	sem_wait(player->ipcs->sem);
//	if (player->ipcs->shm_addr[position_x][position_y])
	sem_post(player->ipcs->sem);
}
