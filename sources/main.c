#include "lem-ipc.h"

int main(int ac, char **av)
{
	t_ipcs		ipcs;
	t_player	player;

	check_input(ac, av);
	create_ipcs(&ipcs);
	fill_player_info(&player, &ipcs, atoi(av[1]));
	return (EXIT_SUCCESS);
}
