#include "lem_ipc.h"

static bool find_upside(
	t_pos *enemy_pos,
	t_player *player,
	const int player_offset)
{
	assert(player_offset > 0);

	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Find upside\n");
	bool is_enemy_found = false;
	int x = player->position.x - player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player->position.y;
		iteration_end = player->position.y + player_offset;
	}
	else
	{
		iteration_start = player->position.y - player_offset;
		iteration_end = player->position.y + (player_offset - 1);
	}
	for (int y = iteration_start; !is_enemy_found && y <= iteration_end; ++y)
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Iteration: x - %d, y - %d\n",
			x,
			y);
		if (!check_out_of_map_bound(x, y, MAP_X)
			&& check_occupied_cell(player->ipcs->shm_addr, x, y, MAP_X)
			&& player->team_number != get_number_from_map(player->ipcs->shm_addr, x, y, TEAM_NUM_CNT, MAP_X))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	}
	return is_enemy_found;
}

static bool find_downside(
	t_pos *enemy_pos,
	t_player *player,
	const int player_offset)
{
	assert(player_offset > 0);

	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Find downside\n");
	bool is_enemy_found = false;
	int x = player->position.x + player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player->position.y;
		iteration_end = player->position.y - player_offset;
	}
	else
	{
		iteration_start = player->position.y + player_offset;
		iteration_end = player->position.y - (player_offset - 1);
	}
	for (int y = iteration_start; !is_enemy_found && y >= iteration_end; --y)
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Iteration: x - %d, y - %d\n",
			x,
			y);
		if (!check_out_of_map_bound(x, y, MAP_X)
			&& check_occupied_cell(player->ipcs->shm_addr, x, y, MAP_X)
			&& player->team_number != get_number_from_map(player->ipcs->shm_addr, x, y, TEAM_NUM_CNT, MAP_X))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	}
	return is_enemy_found;
}

static bool find_rightside(
		t_pos *enemy_pos,
		t_player *player,
		const int player_offset)
{
	assert(player_offset > 0);

	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Find rightside\n");
	bool is_enemy_found = false;
	int y = player->position.y + player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player->position.x;
		iteration_end = player->position.x + player_offset;
	}
	else
	{
		iteration_start = player->position.x - player_offset;
		iteration_end = player->position.x + (player_offset - 1);
	}
	for (int x = iteration_start; !is_enemy_found && x <= iteration_end; ++x)
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Iteration: x - %d, y - %d\n",
			x,
			y);
		if (!check_out_of_map_bound(x, y, MAP_X)
			&& check_occupied_cell(player->ipcs->shm_addr, x, y, MAP_X)
			&& player->team_number != get_number_from_map(player->ipcs->shm_addr, x, y, TEAM_NUM_CNT, MAP_X))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	}
	return is_enemy_found;
}

static bool find_leftside(
		t_pos *enemy_pos,
		t_player *player,
		const int player_offset)
{
	assert(player_offset > 0);

	write_to_log(
		player->logger,
		*player->process_count_mapped,
		"Find leftside\n");
	bool is_enemy_found = false;
	int y = player->position.y - player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player->position.x;
		iteration_end = player->position.x - player_offset;
	}
	else
	{
		iteration_start = player->position.y + player_offset;
		iteration_end = player->position.y - (player_offset - 1);
	}
	for (int x = iteration_start; !is_enemy_found && x >= iteration_end; --x)
	{
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Iteration: x - %d, y - %d\n",
			x,
			y);
		if (!check_out_of_map_bound(x, y, MAP_X)
			&& check_occupied_cell(player->ipcs->shm_addr, x, y, MAP_X)
			&& player->team_number != get_number_from_map(player->ipcs->shm_addr, x, y, TEAM_NUM_CNT, MAP_X))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	}
	return is_enemy_found;
}

t_pos find_enemy(t_player *player)
{
	t_pos enemy_pos = {.x = -1, .y = -1};
	int circle = 0;

	while (++circle)
	{
		if (circle > 20)
			break;
		write_to_log(
			player->logger,
			*player->process_count_mapped,
			"Player PID %d, circle is %d\n",
			getpid(),
			circle);
		if (find_upside(&enemy_pos, player, circle))
			break;
		if (find_downside(&enemy_pos, player, circle))
			break;
		if (find_leftside(&enemy_pos, player, circle))
			break;
		if (find_rightside(&enemy_pos, player, circle))
			break;
	}
	return enemy_pos;
}
