#include "lem_ipc.h"
#include <time.h>

#define BEGIN_RAND_DIAPASON 0
#define END_RAND_DIAPASON MAP_X

void	fill_player_info(t_player *player, t_ipcs *ipcs, int team_number)
{
	player->team_number = team_number;
	player->ipcs = ipcs;
	/// TODO add logger
}

t_pos	get_start_player_position(void)
{
	int position_x;
	int position_y;

	srand(time(NULL));
	position_x = BEGIN_RAND_DIAPASON +
				 (int)(END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	position_y = BEGIN_RAND_DIAPASON +
				 (int)(END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	return (t_pos){position_x, position_y};
}

void	find_starting_place(t_player *player)
{
	t_pos	player_position;
	int		x;
	int		y;

	player_position = get_start_player_position();
	sem_wait(player->ipcs->sem);
	x = -1;
	while (++x < MAP_X)
	{
		y = -1;
		while (++y < MAP_Y)
		{
			if (x == player_position.x && y == player_position.y)
			{
				if (*(player->ipcs->shm_addr + (x + y)) != 0)
					*(player->ipcs->shm_addr + (x + y)) = 1;
			}
		}
	}
	sem_post(player->ipcs->sem);
}
