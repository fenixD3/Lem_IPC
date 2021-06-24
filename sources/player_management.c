#include "lem_ipc.h"
#include <time.h>
#include "logger.h"
#include <stdio.h>
#include "ipc_management.h"

#define BEGIN_RAND_DIAPASON 0
#define END_RAND_DIAPASON (MAP_X - 1)

void init_player(t_player *player)
{
	player->team_number = -1;
	player->team_players = 0;
	player->position.x = -1;
	player->position.y = -1;
	player->ipcs = NULL;
	player->msg_buff = NULL;
	player->logger = NULL;
	player->process_count_mapped = NULL;
}

void fill_player_info(t_player *player, int team_number)
{
	init_player(player);
	get_or_create_mapped_file(FILE_PROCESS_NAME, sizeof(int), (void **)&player->process_count_mapped);
	++*player->process_count_mapped;
	player->team_number = team_number;
	++player->team_players;
	player->ipcs = create_ipcs(*player->process_count_mapped, player->team_players);
	player->msg_buff = create_msg_buff(player->ipcs->mq_attrs->mq_msgsize);
	player->logger = create_logger(*player->process_count_mapped);
	create_log_file(&player->logger->files_info, *player->process_count_mapped);
	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"New player with PID %d in %d team\n",
		getpid(),
		team_number);
	find_starting_place(player);
}

t_pos get_start_player_position(void)
{
	int position_x;
	int position_y;

	srand(time(NULL));
	position_x = BEGIN_RAND_DIAPASON +
			 (int)((float)END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	position_y = BEGIN_RAND_DIAPASON +
			 (int)((float)END_RAND_DIAPASON * rand() / (RAND_MAX + 1.));
	return (t_pos){position_x, position_y};
}

void find_starting_place(t_player *player)
{
	t_pos player_position;

	sem_wait(player->ipcs->sem);
	player_position = get_start_player_position();
	for (bool is_not_placed = true; is_not_placed; player_position = get_start_player_position())
		if (!check_occupied_cell(player->ipcs->shm_addr, player_position.x, player_position.y))
			is_not_placed = false;
	*(player->ipcs->shm_addr + (player_position.x * MAP_X + player_position.y)) = player->team_number + '0';
	player->position = player_position;
	sem_post(player->ipcs->sem);
	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Player PID %d with start position {%d;%d}",
		getpid(),
		player->position.x,
		player->position.y);
}

void delete_player(t_player *player)
{
	--*player->process_count_mapped;
	close_ipcs(player->ipcs);
	if (*player->process_count_mapped == 0)
	{
		destroy_ipcs(player->ipcs, 0);
		write_to_log(player->logger, *player->process_count_mapped, "Destroy logger\n");
		destroy_logger(player->logger);
		unlink(FILE_PROCESS_NAME);
	}
}
