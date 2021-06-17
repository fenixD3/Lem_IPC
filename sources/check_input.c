#include "lem_ipc.h"

void check_input(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s <team number>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	long long team_count = atoll(av[1]);
	if (team_count < 1 || team_count > TEAM_COUNT)
	{
		dprintf(STDERR_FILENO, "Team number (%lld) must be greater"
			 " %d and smaller %d\n", team_count, 1, TEAM_COUNT);
		exit(EXIT_FAILURE);
	}
}
