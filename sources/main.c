#include "lem_ipc.h"


void print_shm(t_ipcs *ipcs)
{
	int		x;
	int		y;

	sem_wait(ipcs->sem);
	x = -1;
	while (++x < (MAP_X * MAP_Y))
	{
		printf("%p: ", ipcs->shm_addr + x);
		y = -1;
		while (++y < MAP_Y)
		{
			printf("[%d]", *(ipcs->shm_addr + (x + y)));
			if (y + 1 == MAP_Y)
				printf("\n");
			else
				printf(" ");
		}
		x += y - 1;
	}
	sem_post(ipcs->sem);
}

int main(int ac, char **av)
{
	t_ipcs		ipcs;
	t_player	player;

	check_input(ac, av);
	create_ipcs(&ipcs);
	fill_player_info(&player, &ipcs, atoi(av[1]));
	find_starting_place(&player);
	print_shm(&ipcs); /// tests
	close_ipcs(&ipcs);
	return (EXIT_SUCCESS);
}
