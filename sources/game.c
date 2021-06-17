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

bool get_message(t_player *player)
{
	if ((mq_receive(player->ipcs->mq, player->msg_buff, player->ipcs->mq_attrs->mq_msgsize, NULL)) == -1)
	{
		if (errno == EAGAIN)
			return false;
		else
		{
			perror("mq_get_message");
			exit(EXIT_FAILURE);
		}
	}
	return true;
}

t_pos get_target_position(t_player *player)
{
	t_pos target_pos;

	if (get_message(player))
		; /// TODO find_target
	else
	{
		sscanf(player->msg_buff, "%d %d", &target_pos.x, &target_pos.y);
	}
}

void game_loop(t_player *player)
{
	while (true)
	{
		sem_wait(player->ipcs->sem);
		if (*player->process_count_mapped == 1)
			return; /// TODO print_winner
		if (check_death(player))
			return;
		get_target_position(player);
		sem_post(player->ipcs->sem);
	}
}
