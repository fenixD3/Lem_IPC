#include "ipc_lib.h"
#include <ctype.h>
#include <assert.h>

bool check_out_of_map_bound(const int x, const int y, const int map_bound)
{
	if (x >= map_bound || y >= map_bound || x < 0 || y < 0)
		return true;
	return false;
}

bool check_occupied_cell(const char *map_addr, const int x, const int y, const int map_bound)
{
	assert(!check_out_of_map_bound(x, y, map_bound));
	if (isdigit(*(map_addr + (x * map_bound + y))))
		return true;
	return false;
}

int get_number_from_map(
	const char *map_addr,
	const int x_offset,
	const int y_offset,
	const int number_length,
	const int map_bound)
{
	return atoi(strndup(map_addr + (x_offset * map_bound + y_offset), number_length));
};
