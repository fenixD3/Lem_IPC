#include "lem_ipc.h"

static t_direction check_direction(const t_pos *player_pos, const t_direction dir)
{
	switch (dir)
	{
	case UP:
	case DOWN:
	case LEFT:
	case RIGHT:
	default:
		return NONE;
	}
}

t_direction get_direction(const t_pos *player_pos, const t_pos *enemy_pos)
{
	int dx, dy, delta;

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

