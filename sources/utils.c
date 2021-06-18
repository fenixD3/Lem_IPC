#include "lem_ipc.h"
#include <ctype.h>

bool check_occupied_cell(const char *map_addr, const int x, const int y)
{
	if (x >= MAP_X || y >= MAP_X)
		return false;
	if (isdigit(*(map_addr + (x * MAP_X + y))))
		return true;
	return false;
}
