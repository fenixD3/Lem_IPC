#include "lem-ipc.h"

int		main(int ac, char **av)
{
	if (!check(ac, av))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
