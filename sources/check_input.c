#include "lem-ipc.h"

bool	check(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "Usage:\n\t%s <team number>", av[0]);
		return (false);
	}
	return (true);
}
