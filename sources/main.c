#include "lem-ipc.h"

int main(int ac, char **av)
{
	t_ipcs ipcs;

	check_input(ac, av);
	create_ipcs(&ipcs);
	return (EXIT_SUCCESS);
}
