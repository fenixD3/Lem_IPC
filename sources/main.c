#include "lem-ipc.h"

int main(int ac, char **av)
{
	check_input(ac, av);
	create_shm();
	return (EXIT_SUCCESS);
}
