#include "lem_ipc.h"
#include <assert.h>

static bool find_upside(
	t_pos *enemy_pos,
	t_pos player_position,
	const int player_offset,
	const char *map_addr,
	const int team_number)
{
	assert(player_offset < 0);

	bool is_enemy_found = false;
	int x = player_position.x - player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player_position.y;
		iteration_end = player_position.y + player_offset;
	}
	else
	{
		iteration_start = player_position.y - player_offset;
		iteration_end = player_position.y + (player_offset - 1);
	}
	for (int y = iteration_start; !is_enemy_found && y <= iteration_end; ++y)
		if (check_occupied_cell(map_addr, x, y) && team_number != atoi(map_addr + (x * MAP_X + y)))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	return is_enemy_found;
}

static bool find_downside(
		t_pos *enemy_pos,
		t_pos player_position,
		const int player_offset,
		const char *map_addr,
		const int team_number)
{
	assert(player_offset < 0);

	bool is_enemy_found = false;
	int x = player_position.x + player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player_position.y;
		iteration_end = player_position.y - player_offset;
	}
	else
	{
		iteration_start = player_position.y + player_offset;
		iteration_end = player_position.y - (player_offset - 1);
	}
	for (int y = iteration_start; !is_enemy_found && y >= iteration_end; --y)
		if (check_occupied_cell(map_addr, x, y) && team_number != atoi(map_addr + (x * MAP_X + y)))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	return is_enemy_found;
}

static bool find_rightside(
		t_pos *enemy_pos,
		t_pos player_position,
		const int player_offset,
		const char *map_addr,
		const int team_number)
{
	assert(player_offset < 0);

	bool is_enemy_found = false;
	int y = player_position.y + player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player_position.x;
		iteration_end = player_position.x + player_offset;
	}
	else
	{
		iteration_start = player_position.x - player_offset;
		iteration_end = player_position.x + (player_offset - 1);
	}
	for (int x = iteration_start; !is_enemy_found && y <= iteration_end; ++y)
		if (check_occupied_cell(map_addr, x, y) && team_number != atoi(map_addr + (x * MAP_X + y)))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	return is_enemy_found;
}

static bool find_leftside(
		t_pos *enemy_pos,
		t_pos player_position,
		const int player_offset,
		const char *map_addr,
		const int team_number)
{
	assert(player_offset < 0);

	bool is_enemy_found = false;
	int y = player_position.y - player_offset;
	int iteration_start, iteration_end;
	if (player_offset == 1)
	{
		iteration_start = player_position.x;
		iteration_end = player_position.x - player_offset;
	}
	else
	{
		iteration_start = player_position.y + player_offset;
		iteration_end = player_position.y - (player_offset - 1);
	}
	for (int x = iteration_start; !is_enemy_found && y >= iteration_end; --y)
		if (check_occupied_cell(map_addr, x, y) && team_number != atoi(map_addr + (x * MAP_X + y)))
		{
			is_enemy_found = true;
			enemy_pos->x = x;
			enemy_pos->y = y;
		}
	return is_enemy_found;
}

t_pos find_enemy_new(t_pos player_position, const char *map_addr, const int team_number)
{
	t_pos enemy_pos = {.x = -1, .y = -1};
	int circle = 0;

	while (++circle)
	{
		if (find_upside(&enemy_pos, player_position, circle, map_addr, team_number))
			break;
		if (find_downside(&enemy_pos, player_position, circle, map_addr, team_number))
			break;
		if (find_leftside(&enemy_pos, player_position, circle, map_addr, team_number))
			break;
		if (find_rightside(&enemy_pos, player_position, circle, map_addr, team_number))
			break;
	}
	assert(enemy_pos.x != -1 || enemy_pos.y != -1);
	return enemy_pos;
}

t_pos find_enemy(t_pos player_position, const char *map_addr, const int team_number)
{
	t_pos enemy_pos = {.x = -1, .y = -1};
	bool is_enemy_found = false;
	int circle = 0;

	while (!is_enemy_found && ++circle)
		for (int x = player_position.x - circle; x <= player_position.x + circle; ++x)
			for (int y = player_position.y - circle; y <= player_position.y + circle; ++y)
				if (check_occupied_cell(map_addr, x, y) && team_number != atoi(map_addr + (x * MAP_X + y)))
				{
					is_enemy_found = true;
					enemy_pos.x = x;
					enemy_pos.y = y;
				}
	assert(enemy_pos.x != -1 || enemy_pos.y != -1);
	return enemy_pos;
}


