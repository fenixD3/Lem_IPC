#include "lem_ipc.h"
#include <ctype.h>

bool check_out_of_map_bound(const int x, const int y)
{
	if (x >= MAP_X || y >= MAP_X || x < 0 || y < 0)
		return true;
	return false;
}

bool check_occupied_cell(const char *map_addr, const int x, const int y)
{
	if (check_out_of_map_bound(x, y))
		return false;
	if (isdigit(*(map_addr + (x * MAP_X + y))))
		return true;
	return false;
}
