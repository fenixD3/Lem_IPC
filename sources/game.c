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
		{
			write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d read MSQ: Empty\n",
				getpid());
			return false;
		}
		else
		{
			perror("mq_get_message");
			exit(EXIT_FAILURE);
		}
	}
	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Player PID %d read MSQ: Success\n",
		getpid());
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
	int dx;
	int dy;
	int delta;

	dx = player_pos->x - enemy_pos->x;
	dy = player_pos->y - enemy_pos->y;
	dx = (dx == 0) ? dy - 1 : dx;
	dy = (dy == 0) ? dx - 1 : dy;
	if ((abs(dx) == 1 && abs(dy) == 1) || (abs(dx) == 1 && dy == 0) || (dx == 0 && abs(dy) == 1))
		return (NONE);
	delta = (abs(dx) > abs(dy)) ? dy : dx;
	if (delta == dx)
	{
		if (dx > 0)
			return (RIGHT);
		return (LEFT);
	}
	else if (dy > 0)
		return (UP);
	return (DOWN);
}

void move_to(t_player *player, const t_pos *enemy_pos)
{
	t_direction direction = get_direction(&player->position, enemy_pos);
	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Player PID %d move to direction %d\n",
		getpid(),
		direction);
	if (direction != NONE)
		(*g_moving[direction])(player, MAP_FILLER);
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
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d found enemy in map\n",
			getpid());
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
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d start his turn\n",
			getpid());
		if (*player->process_count_mapped == 1)
			return print_winner(player);
		if (check_death(player))
		{
			write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d died\n",
				getpid());
			return;
		}
		t_pos enemy_pos = get_enemy_position(player);
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d and position {%d;%d} find enemy with position {%d;%d}\n",
			getpid(),
			player->position.x,
			player->position.y,
			enemy_pos.x,
			enemy_pos.y);
		move_to(player, &enemy_pos);
		sem_post(player->ipcs->sem);
		sleep(3);
	}
}
