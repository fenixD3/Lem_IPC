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
/// неверно двигается к противнику [fix]
/// корды процесса после движения могут уходить в минус [fix]
/// переписать find_enemy на более оптимальный [fix]
/// проверить правильность передвижения по направлениям еще раз (см лог) [fix]
/// умер процесс от одного соседа. Находил как противника и самого себя [fix]
/// какие-то залипания процесса после чтения из очереди [add logs]
/// проскакивают старые данные при чтении в msg_buf [fix]
/// внимательнее дописать обраьотку выбора направления, когда одна из дельт равна 0 [fix (comment ternary dx/dy == 0 ?) + check]
/// иногда проверка найденного противника рядом не работает и процесс занимает с нима одну позицию [fix (replace check) + check]

int main(int ac, char **av)
{
	t_player player;

	check_input(ac, av);
	fill_player_info(&player, atoi(av[1]));
//	print_shm(player.ipcs); /// tests
	sleep(3);
//	print_shm(player.ipcs);
	game_loop(&player);
	delete_player(&player);
	return (EXIT_SUCCESS);
}
