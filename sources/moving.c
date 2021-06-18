#include "lem_ipc.h"

void move_up(t_player *player, const char free_space_filler)
{
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	--player->position.x;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_down(t_player *player, const char free_space_filler)
{
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	++player->position.x;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_left(t_player *player, const char free_space_filler)
{
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	--player->position.y;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}

void move_right(t_player *player, const char free_space_filler)
{
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = free_space_filler;
	++player->position.y;
	*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = player->team_number + '0';
}
