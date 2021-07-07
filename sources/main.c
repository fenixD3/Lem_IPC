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

/// TODO:
/// починить поиск соперника - сейчас находит сам себя [fix]
/// после смерти первого процесса все остальные остаются блокированными в семафоре (add sem_post()) [fix]
/// часто находит на карте соперника с отрицательными кордами [fix]
/// неверно двигается к противнику [fix + check]
/// корды процесса после движения могут уходить в минус [fix + check]
/// переписать find_enemy на более оптимальный [fix + check]

int main(int ac, char **av)
{
	t_player	player;

	check_input(ac, av);
	fill_player_info(&player, atoi(av[1]));
//	print_shm(player.ipcs); /// tests
	sleep(3);
	game_loop(&player);
	delete_player(&player);
	return (EXIT_SUCCESS);
}
