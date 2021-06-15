#include "lem_ipc.h"

bool check_death(const t_player *player)
{
	int enemy_cnt;
	bool is_died;

	enemy_cnt = 0;
	is_died = false;
	sem_wait(player->ipcs->sem);
	for (int x = player->position.x - 1; x <= player->position.x + 1; ++x)
		for (int y = player->position.y - 1; y <= player->position.y + 1; ++y)
		{
			if (check_occupied_cell(player->ipcs->shm_addr, x, y))
				++enemy_cnt;
			if (enemy_cnt == 2)
			{
				is_died = true;
				break;
			}
		}
	sem_post(player->ipcs->sem);
	return is_died;
}
