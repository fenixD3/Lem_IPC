#include "lem_ipc.h"

void start_graphic(const t_player *player)
{
	if (*player->process_count_mapped == 0)
		return;
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execl("Lem_IPC_Ncurses", "Lem_IPC_Ncurses", NULL);
		perror("Lem_IPC_Ncurses");
		exit(EXIT_FAILURE);
	}
}
