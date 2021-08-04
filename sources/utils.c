#include "lem_ipc.h"
#include <ctype.h>
#include <string.h>

bool check_out_of_map_bound(const int x, const int y)
{
	if (x >= MAP_X || y >= MAP_X || x < 0 || y < 0)
		return true;
	return false;
}

bool check_occupied_cell(const char *map_addr, const int x, const int y)
{
	assert(!check_out_of_map_bound(x, y));
	if (isdigit(*(map_addr + (x * MAP_X + y))))
		return true;
	return false;
}

int get_number_from_map(const char *map_addr, const int x_offset, const int y_offset, const int number_length)
{
	return atoi(strndup(map_addr + (x_offset * MAP_X + y_offset), number_length));
};
