#include "lem_ipc.h"


void print_shm(t_ipcs *ipcs)
{
	int		x;
	int		y;

	sem_wait(ipcs->sem);
	x = -1;
	while (++x < MAP_SIZE)
	{
		printf("%p: ", ipcs->shm_addr + x);
		y = -1;
		while (++y < MAP_X)
		{
			printf("[%d]", *(ipcs->shm_addr + (x + y)));
			if (y + 1 == MAP_X)
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
	printf("%s\n", player.logger->files_info->file_name_shm);
	sleep(120);
	close_ipcs(&ipcs);
	destroy_ipcs(&ipcs);
	write_to_log(player.logger, "Destroy logger\n");
	destroy_logger(player.logger);
	return (EXIT_SUCCESS);
}
