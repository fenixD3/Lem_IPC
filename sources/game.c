#include "lem_ipc.h"
#include <ctype.h>
#include <string.h>

bool check_death(const t_player *player)
{
	int enemy_cnt[TEAM_COUNT] = {0};
	int enemy_team;
	bool is_died;

	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Player PID %d check your death\n",
		getpid());
	is_died = false;
	for (int x = player->position.x - 1; !is_died && x <= player->position.x + 1; ++x)
		for (int y = player->position.y - 1; !is_died && y <= player->position.y + 1; ++y)
		{
			if (check_occupied_cell(player->ipcs->shm_addr, x, y)
				&& player->team_number != (enemy_team = atoi(strndup(player->ipcs->shm_addr + (x * MAP_X + y), TEAM_NUM_CNT))))
			{
				++enemy_cnt[enemy_team];
				write_to_log(
					player->logger,
					*player->process_count_mapped,
					"Player PID %d team %d find a new enemy {%d;%d} team %d near itself. Found enemy is %d in team\n",
					getpid(),
					player->team_number,
					x,
					y,
					enemy_team,
					enemy_cnt[enemy_team]);

				for (int team = 0; team < TEAM_COUNT; ++team)
					if (enemy_cnt[team] == 2)
						is_died = true;
			}
		}
	return is_died;
}

bool get_message(t_player *player)
{
	ssize_t read_cnt;
	if ((read_cnt = mq_receive(player->ipcs->mq, player->msg_buff, player->ipcs->mq_attrs->mq_msgsize, NULL)) == -1)
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
			write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d read MSQ: Error - %d\n",
				getpid(),
				errno);
			perror("mq_get_message");
			exit(EXIT_FAILURE);
		}
	}
	player->msg_buff[read_cnt] = '\0';
	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Player PID %d read MSQ: Success\n",
		getpid());
	return true;
}

t_direction get_direction(const t_pos *player_pos, const t_pos *enemy_pos)
{
	int dx;
	int dy;
	int delta;

	dx = player_pos->x - enemy_pos->x;
	dy = player_pos->y - enemy_pos->y;
	if ((abs(dx) == 1 && abs(dy) == 1) || (abs(dx) == 1 && dy == 0) || (dx == 0 && abs(dy) == 1))
		return (NONE);
	if (dx == 0 || dy == 0)
		delta = (dx == 0) ? dy : dx;
	else
		delta = (abs(dx) > abs(dy)) ? dy : dx;
	if (delta == dx)
	{
		if (dx > 0)
			return (UP);
		return (DOWN);
	}
	else if (dy > 0)
		return (LEFT);
	return (RIGHT);
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
	{
		(*g_moving[direction])(player, MAP_FILLER);
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d have new position {%d;%d}\n",
			getpid(),
			player->position.x,
			player->position.y);
	}
	else
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d hasn't got direction\n",
			getpid());

}

t_pos get_enemy_position(t_player *player)
{
	t_pos enemy_pos;
	char message[10];

	if (get_message(player))
		sscanf(player->msg_buff, "%d %d", &enemy_pos.x, &enemy_pos.y);
	else
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"MSQ reading failed\n",
			getpid());
		enemy_pos = find_enemy(player);
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
	printf("Team %d is winner\n", player->team_number);
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
		if (check_death(player))
		{
			write_to_log(
				player->logger,
				*player->process_count_mapped,
				"Player PID %d died\n",
				getpid());
			*(player->ipcs->shm_addr + (player->position.x * MAP_X + player->position.y)) = MAP_FILLER;
			sem_post(player->ipcs->sem);
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
		if (enemy_pos.x == -1 && enemy_pos.y == -1)
			print_winner(player);
		move_to(player, &enemy_pos);
		sem_post(player->ipcs->sem);
		sleep(3);
	}
}
