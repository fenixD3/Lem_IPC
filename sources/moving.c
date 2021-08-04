#include "lem_ipc.h"

void move_up(t_player *player, const char free_space_filler)
{
	if (check_out_of_map_bound(player->position.x - 1, player->position.y))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step: new coordinates is out of map\n",
			getpid());
		return;
	}
	if (check_occupied_cell(player->ipcs->shm_addr, player->position.x - 1, player->position.y))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step: new position is occupied\n",
			getpid());
		return;
	}
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	--player->position.x;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_down(t_player *player, const char free_space_filler)
{
	if (check_out_of_map_bound(player->position.x + 1, player->position.y))
	{
		write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d didn't make a step\n",
				getpid());
		return;
	}
	if (check_occupied_cell(player->ipcs->shm_addr, player->position.x + 1, player->position.y))
	{
		write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d didn't make a step: new position is occupied\n",
				getpid());
		return;
	}
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	++player->position.x;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_left(t_player *player, const char free_space_filler)
{
	if (check_out_of_map_bound(player->position.x, player->position.y - 1))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step\n",
			getpid());
		return;
	}
	if (check_occupied_cell(player->ipcs->shm_addr, player->position.x, player->position.y - 1))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step: new position is occupied\n",
			getpid());
		return;
	}
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	--player->position.y;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_right(t_player *player, const char free_space_filler)
{
	if (check_out_of_map_bound(player->position.x, player->position.y + 1))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step\n",
			getpid());
		return;
	}
	if (check_occupied_cell(player->ipcs->shm_addr, player->position.x, player->position.y + 1))
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d didn't make a step: new position is occupied\n",
			getpid());
		return;
	}
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	++player->position.y;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}
