#include "lem-ipc.h"

void check_input(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "Usage: %s <team number>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (av[1] < 0 || atoll(av[1]) > TEAM_COUNT)
	{
		dprintf(2, "Team number (%lld) must be greater"
			 " %d and smaller %d\n", atoll(av[1]), 0, TEAM_COUNT);
		exit(EXIT_FAILURE);
	}
}
