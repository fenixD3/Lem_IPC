#include "lem_ipc.h"
#include <ctype.h>
#include <assert.h>
#include <string.h>

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
			if (check_occupied_cell(player->ipcs->shm_addr, x, y) && player->team_number != isdigit(*(player->ipcs->shm_addr + (x * MAP_X + y))))
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

t_pos find_enemy(t_pos player_position, const char *map_addr, const int team_number)
{
	t_pos enemy_pos = {.x = -1, .y = -1};
	bool is_enemy_found = false;
	int circle = 0;

	while (!is_enemy_found && ++circle)
		for (int x = player_position.x - circle; x <= player_position.x + circle; ++x)
			for (int y = player_position.y - circle; y <= player_position.y + circle; ++y)
				if (check_occupied_cell(map_addr, x, y) && team_number != isdigit(*(map_addr + (x * MAP_X + y))))
				{
					is_enemy_found = true;
					enemy_pos.x = x;
					enemy_pos.y = y;
				}
	assert(enemy_pos.x != -1 || enemy_pos.y != -1);
	return enemy_pos;
}

t_direction get_direction(const t_pos *player_pos, const t_pos *enemy_pos)
{
	/// TODO
}

void move_to(t_player *player, const t_pos *enemy_pos)
{
	get_direction(&player->position, enemy_pos);
}

t_pos get_enemy_position(t_player *player)
{
	t_pos enemy_pos;
	char message[10];

	if (get_message(player))
		sscanf(player->msg_buff, "%d %d", &enemy_pos.x, &enemy_pos.y);
	else
	{
		enemy_pos = find_enemy(player->position, player->ipcs->shm_addr, player->team_number);
		sprintf(message, "%d %d", enemy_pos.x, enemy_pos.y);
		mq_send(player->ipcs->mq, message, strlen(message), 0); /// TODO may be need send message n time (n - count process in team)
	}
	return enemy_pos;
}

static void print_winner(const t_player *player)
{
	printf("Team %d is winner", player->team_number);
}

void game_loop(t_player *player)
{
	while (true)
	{
		sem_wait(player->ipcs->sem);
		if (*player->process_count_mapped == 1)
			return print_winner(player);
		if (check_death(player))
			return;
		t_pos enemy_pos = get_enemy_position(player);
		move_to(player, &enemy_pos);
		sem_post(player->ipcs->sem);
	}
}
