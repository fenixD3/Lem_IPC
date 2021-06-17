#include "lem_ipc.h"
#include <ctype.h>

void print_shm(t_ipcs *ipcs)
{
	sem_wait(ipcs->sem);
	for (int x = 0; x < MAP_SIZE; x += MAP_X)
	{
		printf("%p: ", ipcs->shm_addr + x);
		for (int y = 0; y < MAP_X; ++y)
		{
			printf("%c", *(ipcs->shm_addr + (x + y)));
			if (y + 1 == MAP_X)
				printf("\n");
			else
				printf(" ");
		}
	}
	sem_post(ipcs->sem);
}

int main(int ac, char **av)
{
	t_player	player;

	check_input(ac, av);
	fill_player_info(&player, atoi(av[1]));
//	print_shm(player.ipcs); /// tests
	sleep(5);
	game_loop(&player);
	delete_player(&player);
	return (EXIT_SUCCESS);
}
